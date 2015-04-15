#include "SimpleClient.h"
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <algorithm>

SimpleClient::SimpleClient(Connection &connection)
    : state_machine(GET_IDENTITY, *this), 
      connection(connection),
      last_turn_position() {
}

SimpleClient::~SimpleClient() {
}

SimpleClient::StateMachineType::StateMap SimpleClient::get_state_map() {
    StateMachineType::StateMap map;
    map[GET_IDENTITY] = &SimpleClient::get_identity;
    map[WAIT_FOR_GAME_START] = &SimpleClient::wait_for_game_start;
    map[YOUR_TURN] = &SimpleClient::your_turn;
    return map;
}

std::string SimpleClient::ask_user(std::string prompt, std::string default_value) {
    if(std::cin.eof()) throw std::runtime_error("user input requested, but stdin is already closed.");
    std::string value;
    std::cout << prompt << std::flush;
    std::cin >> value;
    if(!std::cin.good()) value = default_value;
    return value;
}

void SimpleClient::ask_ship_placement() {
    while(!you.get_battle_field().all_ships_placed()) {
        print_battle_field(you);
        print_ships_available();
        auto length = ask_ship_length();
        auto orientation = ask_ship_orientation();
        auto position = ask_position();
        try {
            you.get_battle_field().add_ship(length, orientation, position);
        } catch(std::out_of_range &ex) {
            std::cout << "error: " << ex.what() << std::endl;
        } catch(std::invalid_argument &ex) {
            std::cout << "error: " << ex.what() << std::endl;
        }
    }
}

unsigned int SimpleClient::ask_ship_length() {
    unsigned int chosen_length = 0;
    auto ships_available = you.get_battle_field().get_ships_available();
    bool ok = false;
    while(!ok) {
        try {
            std::string input = ask_user("Choose Length: ", "-");
            chosen_length = boost::lexical_cast<unsigned int>(input);
            if(ships_available.find(chosen_length) != ships_available.end()) {
                if(ships_available[chosen_length] > 0) {
                    ok = true;
                } else {
                    std::cout << "no more " << get_ship_name_by_length(chosen_length) << "s available" << std::endl;
                }
            } else {
                std::cout << "error: there are no ships of length " << chosen_length << std::endl;
            }
        } catch(boost::bad_lexical_cast&) {
            std::cout << "error: invalid input. enter a whole positive number" << std::endl;
        }
    }
    return chosen_length;
}

orientation_t SimpleClient::ask_ship_orientation() {
    orientation_t orientation = ORIENTATION_HORIZONTAL;
    bool ok = false;
    while(!ok) {
        std::string input = ask_user("Choose Orientation ([v]ertical/[h]orizontal): ", "");
        if(input == "v" || input == "h") {
            orientation = input == "v" ? ORIENTATION_VERTICAL : ORIENTATION_HORIZONTAL;
            ok = true;
        } else {
            std::cout << "error: invalid orienation. type either 'v' or 'h'." << std::endl;
        }
    }
    return orientation;
}

position_t SimpleClient::ask_position() {
    position_t position;
    bool ok = false;
    while(!ok) {
        position.y = ask_coord("y");
        position.x = ask_coord("x");
        if(check_position(position, BATTLEFIELD_HEIGHT, BATTLEFIELD_WIDTH)) {
            ok = true;
        } else {
            std::cout << "error: out of bounds." << std::endl;
        }
    }
    return position;
}

void SimpleClient::ask_turn() {
        print_battle_field(enemy);
        print_battle_field(you);

        std::cout << "Enter enemy field you want to hit." << std::endl;
        last_turn_position = ask_position();

        TurnPackage turn;
        turn.set_identity(you.get_identity());
        turn.set_position(last_turn_position);
        connection.write(turn);
}

position_coordinate_t SimpleClient::ask_coord(std::string coord_name) {
    position_coordinate_t coord = 0;
    bool ok = false;
    while(!ok) {
        try {
            std::string input = ask_user("Choose Position (" + coord_name + "): ", "");
            coord = boost::lexical_cast<position_coordinate_t>(input);
            ok = true;
        } catch(boost::bad_lexical_cast&) {
            std::cout << "error: invalid input. enter a whole postive number" << std::endl;
        }
    }
    return coord;
}

void SimpleClient::print_ships_available() {
    auto ships_available = you.get_battle_field().get_ships_available();
    std::cout  << " name             | length | available " << std::endl;
    std::cout  << "------------------+--------+-----------" << std::endl;
    std::for_each(ships_available.begin(), ships_available.end(), [this](std::pair<unsigned int, int> pair) {
        const unsigned int length = pair.first;
        const int number_available = pair.second;
        std::cout << " "   << std::setw(16) << get_ship_name_by_length(length)
                  << " | " << std::setw(6) << length
                  << " | " << std::setw(8) << number_available
                  << std::endl;
        
    });
}

std::string SimpleClient::get_ship_name_by_length(unsigned int length) {
    std::string ship_names[] = {"Destroyer", "Cruiser", "Battleship", "Aircraft Carrier"};
    if(length >= 2 && length <= 5) {
        return ship_names[length - 2];
    }
    return std::string("(invalid ship)");
}

void SimpleClient::print_battle_field(Player & player) {
    int x = 0, y = 0;
    std::vector<int> x_numbers(BATTLEFIELD_WIDTH), y_numbers(BATTLEFIELD_HEIGHT);
    std::generate_n(x_numbers.begin(), BATTLEFIELD_WIDTH, [&x]() { return x++; });
    std::generate_n(y_numbers.begin(), BATTLEFIELD_HEIGHT, [&y]() { return y++; });

    std::string under_line = std::string(BATTLEFIELD_WIDTH * 2 + 1, '_');
    std::stringstream ss;
    std::for_each(x_numbers.begin(), x_numbers.end(), [&](int x) { ss << std::setw(2) << x; });
    std::string number_line = ss.str();

    std::cout << " " << under_line << std::endl;
    std::cout << "/ " << std::setw(PLAYER_NAME_MAX_LENGTH) << player.get_name() << " \\" << std::endl;
    std::cout << "|" << number_line << " x" << std::endl;
    
    auto fields = player.get_battle_field().to_vector();
    for(int y = 0; y < BATTLEFIELD_HEIGHT; y++) {
        std::cout << std::setw(1) << y_numbers[y];
        for(int x = 0; x < BATTLEFIELD_WIDTH; x++) {
            std::cout << std::setw(2) << fields[y][x];
        }
        std::cout << std::setw(2) << y_numbers[y];
        std::cout << std::endl;
    }
    std::cout << "y" << number_line << " |" << std::endl;
    std::cout << "\\" << under_line  << "/" << std::endl;
}

void SimpleClient::run() {
    std::string name = ask_user("Your Nickname: ", "unnamed");
    you.set_name(name);
    PlayerJoinPackage player_join_package;
    player_join_package.set_player_name(name);
    connection.write(player_join_package);

    static std::function<void(void)> get_input;
    get_input = [this]() -> void {
        connection.read([this](NetworkPackage& command) {
            ServerNetworkPackage package(command);
            state_machine.run_state(package);
            get_input();
        });
    };
    get_input();
}


SimpleClientState SimpleClient::get_identity(ServerNetworkPackage server_package) {
    std::cout << "get identity" << std::endl;
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<PlayerJoinAnswerPackage>(package)) {
         PlayerJoinAnswerPackage & answer = cast_package<PlayerJoinAnswerPackage>(package);
         you.set_identity(answer.get_identity());
         std::cout << "identity: " << you.get_identity() << std::endl;
        return WAIT_FOR_GAME_START;
    }
    return GET_IDENTITY;
}

SimpleClientState SimpleClient::wait_for_game_start(ServerNetworkPackage server_package) {
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<GameReadyPackage>(package)) {
        GameReadyPackage & game_ready_package = cast_package<GameReadyPackage>(package);
        enemy.set_name(game_ready_package.get_enemy_name());
        ask_ship_placement();
        ShipPlacementPackage ship_placement_package;
        ship_placement_package.set_identity(you.get_identity());
        ship_placement_package.set_ship_data(you.get_battle_field().get_ship_data());
        connection.write(ship_placement_package);
        std::cout << "waiting for confirmation ... " << std::endl;
    } else if(is_package_of_type<ShipPlacementResponsePackage>(package)) {
        auto &response = cast_package<ShipPlacementResponsePackage>(package);
        if(response.get_valid()) {
            std::cout << "your ship placement has been confirmed." << std::endl;
            std::cout << "waiting for your first turn to start ... " << std::endl;
            return YOUR_TURN;
        } else {

            std::cout << "error: server rejected ship placement, because ";
            if(response.get_out_of_bounds()) {
                std::cout << "some ships where out of bounds";
            } else if(response.get_ships_overlap()) {
                std::cout << "some ships overlap";
            } else if(response.get_remaining_ships() > 0) {
                std::cout << "you didn't place all the ships";
            } else if(response.get_remaining_ships() < 0) {
                std::cout << "you placed too many ships";
            } else {
                std::cout << "of an unknown reason";
            }
            std::cout << std::endl;
            std::cout << "so, let's place the ships again! yay!" << std::endl;
            you.get_battle_field().clear();
            ask_ship_placement();
            ShipPlacementPackage ship_placement_package;
            ship_placement_package.set_identity(you.get_identity());
            ship_placement_package.set_ship_data(you.get_battle_field().get_ship_data());
            connection.write(ship_placement_package);
            std::cout << "waiting for confirmation ... " << std::endl;
        }
    }
    return WAIT_FOR_GAME_START;
}

SimpleClientState SimpleClient::your_turn(ServerNetworkPackage server_package) {
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<TurnRequestPackage>(package)) {
        auto& turn_request = cast_package<TurnRequestPackage>(package);
        if(turn_request.get_enemy_hit()) {
            you.get_battle_field().hit_field(turn_request.get_position());
        }
        ask_turn();
        std::cout << "wait for confirmation ... " << std::endl;
    } else if(is_package_of_type<TurnResponsePackage>(package)) {
        auto& turn_response = cast_package<TurnResponsePackage>(package);
        if(!turn_response.get_valid()) {
            std::cout << "error: invalid turn, try again" << std::endl;
            ask_turn();
            std::cout << "wait for confirmation ... " << std::endl;
        } else {
            auto field = enemy.get_battle_field().get_field(last_turn_position);
            field->set_ship_part(turn_response.get_ship_hit());
            field->set_hit();
            std::cout << (turn_response.get_ship_hit()
                         ? "you hit an enemy ship!"
                         : "you missed!") << std::endl;
            std::cout << "wait for enemy player to make his turn ... " << std::endl;
        }
    } else if(is_package_of_type<EnemyDisconnectedPackage>(package)) {
        std::cout << "the enemy disconnected ... well i guess you won?" << std::endl;
    } else if(is_package_of_type<GameEndedPackage>(package)) {
        auto& end_package= cast_package<GameEndedPackage>(package);
        if(end_package.get_won()) {
            std::cout << "Congratz! You Won! \\o/" << std::endl;
        } else {
            std::cout << "You lost :-(" << std::endl;
        }

        std::cout << "Here's the enemy's field with his ships: " << std::endl;
        auto ship_data = end_package.get_enemy_ships();
        enemy.get_battle_field().add_ship_data(ship_data);
        print_battle_field(enemy);

        std::cout << "Until next time!" << std::endl;

    }
    return YOUR_TURN;
}
