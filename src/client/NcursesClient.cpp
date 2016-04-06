#include "EnhancedClient.h"
#include <boost/log/trivial.hpp>

NcursesClient::NcursesClient()
{
    visible_home = true;
    initscr();
}

NcursesClient::~NcursesClient()
{
    endwin();
    delscreen(stdscr);
}

/**
 * This function connects the events to the corresponding functionality
 */
void NcursesClient::setup()
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

/**
 * calculates the position and the draws the general part of the UI.
 * general parts are:
 *  - empty space for 2 battle fields
 *  - command center statitics
 *  - command center log
 *
 */
void NcursesClient::draw_general_UI()
{
    int width = getmaxx(stdscr) / 3;
    int height = getmaxy(stdscr);
    int log_height = height-STATISTIC_HEIGHT-CORRECTOUR;
    statistics = std::unique_ptr<CommandCenterStatistics>
        (
            new CommandCenterStatistics(STATISTIC_HEIGHT, width, 2*width,0)
        );

    combat_log = std::unique_ptr<CommandCenterCombatLog>
        (
            new CommandCenterCombatLog(log_height, width, 2*width,STATISTIC_HEIGHT+1)
        );
}

/**
 * given the GameConfiguration 'config' it calculates the field size and position
 * and draws the 2 battlefields into the empty space.
 *
 */
void NcursesClient::draw_battlefield_UI(GameConfiguration config)
{
    home_field = std::unique_ptr<BattleFieldUI>
        (
            new BattleFieldUI(10,height/3,stdscr,config)
        );

    enemy_field = std::unique_ptr<BattleFieldUI>
        (
            new BattleFieldUI(width + 10, height/3,stdscr,config)
        );
}

/**
 * moves the cursor around on the own battle field to read cursor position
 * and adds a ship to the field at start_pos and end_pos.
 * The field of the server's player and UI player object.
 *
 * @param - Player object 'you' given from the server
 */
void NcursesClient::set_fleet(Player &you)
{

}

/**
 * checks the validation of the ship andn defines its orientation.
 * then it adds the ship to the players battle field
 */
void NcursesClient::add_ship_to_field(position_t start_pos, position_t end_pos)
{

}

/**
 * is called to read the position of target 
 *
 * @return - the position from type position_t
 */
position_t NcursesClient::set_target()
{

}


