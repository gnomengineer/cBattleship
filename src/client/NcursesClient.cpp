#include "EnhancedClient.h"
#include <boost/log/trivial.hpp>

NcursesClient::NcursesClient()
{

}

NcursesClient::~NcursesClient()
{

}

/**
 * This function connects the events to the corresponding functionality
 */
NcursesClient::setup()
{
    /********************************
     * START connecting Game Events *
     *******************************/

    //when trying to establish a connection
    client_state_machine.events.connecting.connect(
        [](std::string host, unsigned int port)
        {
            combat_log->log_message("client is trying to connect to server...");
        }
    );

    //when client connected to server
    client_state_machine.events.connected.connect(
        []()
        {
            combat_log->log_message("connection established");
        }
    );

    //when game configuration is sent
    client_state_machine.events.get_game_configuration.connect(
        [](GameConfiguration config)
        {
            draw_battlefield_UI(&config);
        }
    );

    //when server asks for player name
    client_state_machine.events.get_player_name.connect(
        [](std::string &name)
        {
            combat_log->log_message("write your name");
            std::cin >> name;
        }
    );

    //when server asks for ship placement
    client_state_machine.events.place_ships.connect(
        [](Player &you)
        {
            set_fleet(you);
        }
    );

    //when placed ships are invalid
    client_state_machine.events.place_ship_error.connect(
        [](bool out_of_bounds, bool overlap, int remaining_ships)
        {
            if(out_of_bounds)combat_log->log_message("Some ships were out of bound");
            if(overlap)combat_log->log_message("Some ships overlap each other");
        }
    );

    //when server asks for target position
    client_state_machine.events.get_turn.connect(
        [](Player &you, Player &enemy, position_t &position)
        {
            position = set_target();
        }
    );

    //when given position is invalid
    client_state_machine.events.turn_error.connect(
        []()
        {
            combat_log->log_message("your target position is not valid");
        }
    );

    //when given position is valid
    client_state_machine.events.turn_ok.connect(
        [](bool did_you_hit, int ship_of_length_destroyed)
        {
            update_after_turn(did_you_hit);
        }
    );

    //when client has to wait for opponent
    client_state_machine.events.enemy_wait.connect(
        []()
        {
            combat_log->log_message("wait until the enemy has shot...");
        }
    );

    //when game has ended
    client_state_machine.events.game_ended.connect(
        [](bool won, Player &you, Player &enemy)
        {
            game_end_UI(won);
        }
    );
    /*******************************
     * STOP connecting Game Events *
     ******************************/
}
