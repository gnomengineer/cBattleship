#include "SimpleClient.h"
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <algorithm>

SimpleClient::SimpleClient(Connection &connection)
    : state_machine(GET_IDENTITY, *this),  connection(connection) {
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
        position.y = ask_ship_coord("y");
        position.x = ask_ship_coord("x");
        if(position.y <= BATTLEFIELD_HEIGHT && position.x <= BATTLEFIELD_WIDTH) {
            ok = true;
        } else {
            std::cout << "error: out of bounds." << std::endl;
        }
    }
    return position;
}

position_coordinate_t SimpleClient::ask_ship_coord(std::string coord_name) {
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
    std::cout << " " << std::string(BATTLEFIELD_WIDTH - 2, '_') << " " << std::endl;
    std::cout << "/ " << std::setw(BATTLEFIELD_WIDTH - 4) << player.get_name() << " \\" << std::endl;
    auto fields = player.get_battle_field().to_vector();
    for(int y = 0; y < BATTLEFIELD_HEIGHT; y++) {
        std::string line(fields[y].begin(), fields[y].end());
        std::cout << line << std::endl;
    }
    std::cout << "\\" << std::string(BATTLEFIELD_WIDTH - 2, '_') << "/" << std::endl;
}

void SimpleClient::run() {
    std::string name = ask_user("your nickname: ", "unnamed");
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
        ask_ship_placement();
        ShipPlacementPackage ship_placement_package;
        ship_placement_package.set_identity(you.get_identity());
        ship_placement_package.set_ship_data(you.get_battle_field().get_ship_data());
        connection.write(ship_placement_package);
        std::cout << "waiting for enemy ... " << std::endl;
    }
    return YOUR_TURN;
}

SimpleClientState SimpleClient::your_turn(ServerNetworkPackage server_package) {
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<TurnRequestPackage>(package)) {
        print_battle_field(enemy);
        print_battle_field(you);
        TurnPackage turn;
        turn.set_identity(you.get_identity());
        std::cout << "Enter enemy field you want to hit." << std::endl;
        position_t position = ask_position();
        connection.write(turn);
        std::cout << "waiting for enemy ... " << std::endl;
    } else if(is_package_of_type<EnemyDisconnectedPackage>(package)) {
        std::cout << "the enemy disconnected ... well i guess you won?" << std::endl;
    }
    return YOUR_TURN;
}
