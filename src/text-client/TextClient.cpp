#include "TextClient.h"
#include <common/GameConfiguration.h>
#include <boost/lexical_cast.hpp>

TextClient::TextClient(std::string connection_string)
    : client_state_machine(connection_string) {
    client_state_machine.events.connecting.connect([](std::string connection_string) {
        std::cout << "trying to connect to '" << connection_string << "' ... " << std::endl;
    });

    client_state_machine.events.connected.connect([]() {
        std::cout << "trying to join server... " << std::endl;
    });

    client_state_machine.events.get_game_configuration.connect([](GameConfiguration config) {
        std::cout << "Game Configuration: " << std::endl;
        std::cout << " * The board size is " << config.get_size_y() <<  " in height" << std::endl;
        std::cout << " * The board size is " << config.get_size_x() <<  " in width" << std::endl;
        std::cout << " * You " << (config.get_hitspree() ? "can" : "can't") << " shoot again if you hit an enemy ship" << std::endl;
        std::cout << std::endl;
    });

    client_state_machine.events.get_player_name.connect([this](std::string &name) {
        name = ask_user("Your Nickname: ", "unnamed");
    });

    client_state_machine.events.new_identity.connect([](std::string identity) {
         std::cout << "identity: " << identity << std::endl;
    });

    client_state_machine.events.place_ships.connect([this](Player &you) {
        ask_ship_placement(you);
    });

    client_state_machine.events.place_ship_ok.connect([]() {
        std::cout << "your ship placement has been confirmed." << std::endl;
        std::cout << "waiting for your first turn to start ... " << std::endl;
    });

    client_state_machine.events.place_ship_confirmation_wait.connect([]() {
        std::cout << "waiting for confirmation ... " << std::endl;
    });

    client_state_machine.events.place_ship_error.connect([](bool out_of_bounds, bool overlap, int remaining_ships) {
        std::cout << "error: server rejected ship placement, because ";
        if(out_of_bounds) {
            std::cout << "some ships where out of bounds";
        } else if(overlap) {
            std::cout << "some ships overlap";
        } else if(remaining_ships > 0) {
            std::cout << "you didn't place all the ships";
        } else if(remaining_ships < 0) {
            std::cout << "you placed too many ships";
        } else {
            std::cout << "of an unknown reason";
        }
        std::cout << std::endl;
        std::cout << "so, let's place the ships again! yay!" << std::endl;

    });

    client_state_machine.events.get_turn.connect([this](Player &you, Player &enemy, position_t &position) {
        position = ask_turn(you, enemy);
    });

    client_state_machine.events.turn_confirmation_wait.connect([]() {
        std::cout << "waiting for confirmation ... " << std::endl;
    });

    client_state_machine.events.turn_ok.connect([this](bool did_you_hit, int ship_of_length_destroyed) {
        std::cout << (did_you_hit
                     ? "you hit an enemy ship!"
                     : "you missed!") << std::endl;
        if(ship_of_length_destroyed > 0) {
            std::cout << "you destroyed an enemy " << get_ship_name_by_length(ship_of_length_destroyed) << " (" << ship_of_length_destroyed << ")!" << std::endl;
        }
    });

    client_state_machine.events.turn_error.connect([]() {
        std::cout << "error: invalid turn, try again" << std::endl;
    });

    client_state_machine.events.enemy_hit.connect([](bool hit, position_t position) {
        if(hit) {
            std::cout << "You've been hit at (" << position.x << "|" << position.y << ")" << std::endl;
        } else {
            std::cout << "The enemy missed" << std::endl;
        }
    });


    client_state_machine.events.enemy_wait.connect([]() {
            std::cout << "wait for enemy player to make his turn ... " << std::endl;
    });

    client_state_machine.events.enemy_disconnected.connect([]() {
        std::cout << "the enemy disconnected ... well i guess you won?" << std::endl;
    });

    client_state_machine.events.game_ended.connect([this](bool won, Player &you, Player &enemy) {
        if(won) {
            std::cout << "Congratz! You Won! \\o/" << std::endl;
        } else {
            std::cout << "You lost :-(" << std::endl;
        }

        std::cout << "Here's the enemy's field with his ships: " << std::endl;
        print_battle_field(enemy);
        std::cout << "Until next time!" << std::endl;
    });

}

TextClient::~TextClient() {
}

std::string TextClient::ask_user(std::string prompt, std::string default_value) {
    if(std::cin.eof()) throw std::runtime_error("user input requested, but stdin is already closed.");
    std::string value;
    std::cout << prompt << std::flush;
    std::cin >> value;
    if(!std::cin.good()) value = default_value;
    return value;
}

void TextClient::ask_ship_placement(Player &you) {
    auto &battle_field = you.get_battle_field();
    while(!battle_field.all_ships_placed()) {
        print_battle_field(you);
        print_ships_available(you.get_battle_field());
        auto length = ask_ship_length(you);
        auto orientation = ask_ship_orientation();
        auto position = ask_position(you);
        try {
            you.get_battle_field().add_ship(length, orientation, position);
        } catch(std::out_of_range &ex) {
            std::cout << "error: " << ex.what() << std::endl;
        } catch(std::invalid_argument &ex) {
            std::cout << "error: " << ex.what() << std::endl;
        }
    }
}

unsigned int TextClient::ask_ship_length(Player &you) {
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

orientation_t TextClient::ask_ship_orientation() {
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

position_t TextClient::ask_position(Player &you) {
    position_t position;
    bool ok = false;
    while(!ok) {
        auto &battle_field = you.get_battle_field();
        position.y = ask_coord("y");
        position.x = ask_coord("x");
        if(check_position(position, battle_field.get_size_y(), battle_field.get_size_x())) {
            ok = true;
        } else {
            std::cout << "error: out of bounds." << std::endl;
        }
    }
    return position;
}

position_t TextClient::ask_turn(Player &you, Player &enemy) {
        print_battle_field(enemy);
        print_battle_field(you);

        std::cout << "Enter enemy field you want to hit." << std::endl;
        position_t position = ask_position(you);

        return position;
}

position_coordinate_t TextClient::ask_coord(std::string coord_name) {
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

void TextClient::print_ships_available(BattleField &battlefield) {
    auto ships_available = battlefield.get_ships_available();
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

std::string TextClient::get_ship_name_by_length(unsigned int length) {
    std::string ship_names[] = {"Cruiser", "Destroyer", "Battleship", "Aircraft Carrier"};
    if(length >= 2 && length <= 5) {
        return ship_names[length - 2];
    }
    return std::string("(invalid ship)");
}

void TextClient::print_battle_field(Player & player) {
    int x = 0, y = 0;
    auto &battle_field = player.get_battle_field();
    const unsigned int width = battle_field.get_size_x();
    const unsigned int height = battle_field.get_size_y();
    std::vector<int> x_numbers(width), y_numbers(height);
    std::generate_n(x_numbers.begin(), width, [&x]() { return x++; });
    std::generate_n(y_numbers.begin(), height, [&y]() { return y++; });

    std::string under_line = std::string(width * 2 + 1, '_');
    std::stringstream ss;
    std::for_each(x_numbers.begin(), x_numbers.end(), [&](int x) { ss << std::setw(2) << x; });
    std::string number_line = ss.str();

    std::cout << " " << under_line << std::endl;
    std::cout << "/ " << std::setw(width * 2 - 1) << player.get_name() << " \\" << std::endl;
    std::cout << "|" << number_line << " x" << std::endl;
    
    auto fields = player.get_battle_field().to_vector();
    for(int y = 0; y < height; y++) {
        std::cout << std::setw(1) << y_numbers[y];
        for(int x = 0; x < width; x++) {
            std::cout << std::setw(2) << fields[y][x];
        }
        std::cout << std::setw(2) << y_numbers[y];
        std::cout << std::endl;
    }
    std::cout << "y" << number_line << " |" << std::endl;
    std::cout << "\\" << under_line  << "/" << std::endl;
}

void TextClient::run() {
    client_state_machine.run();
}
