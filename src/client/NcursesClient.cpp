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

    //when the enemy has hit you
    client_state_machine.events.enemy_hit.connect(
        [](bool hit, position_t position)
        {
            update_after_turn(hit, home_field, position);
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
    bool begin_ship = true;
    bool quit_insert_ship = false;

    position_t start_pos;
    position_t end_pos;

    home_field->move_cursor(1,1);
    curs_set(1);

    while(!(quit_insert_ship)
    {
        int input = getch();
        int x = getcurx(home_field->get_window());
        int y = getcury(home_field->get_window());
        switch (input)
        {
            case '\n':
                if(begin_ship)
                {
                    start_pos = home_field->get_position();
                    begin_ship = false;
                }
                else
                {
                    end_pos = home_field->get_position();
                    begin_ship = true;
                    try
                    {
                        add_ship_to_field(start_pos,end_pos);
                        home_field->draw_content();
                    }
                    catch(std::out_of_range &ex)
                    {
                        combat_log->log_message(ex.what());
                    }
                    catch(std::invalid_argument &ex)
                    {
                        combat_log->log_message(ex.what());
                    }
                }
                
                break;
            case KEY_RIGHT:
                home_field->move_cursor(++x,y);
                break;
            case KEY_LEFT:
                home_field->move_cursor(--x,y);
                break;
            case KEY_UP:
                home_field->move_cursor(x,--y);
                break;
            case KEY_DOWN:
                home_field->move_cursor(x,++y);
                break;
            case 'q':
                quit_insert_ship = true;
                combat_log->log_message("Fleet is positioned");
                break; 
            default:
                break;
        }
    }
    curs_set(0);
}

/**
 * checks the validation of the ship andn defines its orientation.
 * then it adds the ship to the players battle field
 */
void NcursesClient::add_ship_to_field(position_t start_pos, position_t end_pos)
{

}

/**
 * is called to read the position of target. It returns the position for the game server and writes the position also into 'last_target' for processing later. 
 *
 * @return - the position from type position_t
 */
position_t NcursesClient::set_target()
{

}

/**
 * This method is called from the event turn_ok when your shot was valid.
 * in the parameter is the value if you hit or not.
 * 
 * This method calls a second 'update_after_turn' with additional parameters
 * like 'enemy_field' as battlefieldUI object and 'last_target' as position_t
 *
 * 
 * @param - bool if shot has hit a target (true) or not (false)
 */
void NcursesClient::update_after_turn(bool did_you_hit)
{
   update_after_turn(did_you_hit, enemy_field, last_target); 
}

/**
 * This method reprints the given 'battlefield' and updates the given 'position' on the field before print according to the 'was_hit' parameter.
 *
 * @param - was_hit if the last shot on the given battle field was successful
 * @param - battlefield object of the current battle field the shot refers to
 * @param - position where the shot has hit on the battle field
 */
void NcursesClient::update_after_turn(bool was_hit, BattleFieldUI& battlefield, position_t position)
{

}

/**
 * when all ships of one participant are destroyed the end window UI is printed.
 * It requries a boolean to print either loose or won on the screen
 */
void NcursesClient::game_end_UI(bool win)
{

}

/**
 * Toggles the visibility of the home_field
 */
void NcursesClient::toggle_home()
{

    
}
