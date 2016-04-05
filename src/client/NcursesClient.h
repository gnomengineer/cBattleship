#ifndef ENHANCEDCLIENT_H
#define ENHANCEDCLIENT_H

#include <clientlib/Player.h>
#include <clientlib/ClientStateMachine.h>
#include "BattleFieldUI.h"
#include "CommandCenterStatistics.h"
#include "CommandCenterCombatLog.h"
#include <common/position.h>

#define STATISTIC_HEIGHT 14

class NcursesClient
{

private:
    std::unique_ptr<BattleFieldUI> home_field;
    std::unique_ptr<BattleFieldUI> enemy_field;

    std::unique_ptr<CommandCenterStatistics> statistics;
    std::unique_ptr<CommandCenterCombatLog> combat_log;

    std::unique_ptr<WinScreen> end_ui;

    ClientStateMachine client_state_machine;

    bool visible_home;
public:
    NcursesClient();
    virtual ~NcursesClient();
    void setup();
private:
    void run(std::string connection_string);

    void draw_general_UI();

    //calculates position and displays UI
    //connected to the 'get_game_configuration' event
    void draw_battlefield_UI(GameConfiguration config);

    //requests the user to set his fleet
    //connected to the 'place_ships' event
    void set_fleet(Player you);

    //adds ship to the field
    void add_ship_to_field(position_t start_pos, position_t end_pos);

    //requests the user to call a target to shoot
    //connected to the 'get_turn' event
    position_t set_target();

    //marks the target field previously shot according to hit
    //connected to the 'turn_ok' event
    void update_after_turn(bool did_you_hit);

    //displays the game over screen with win/loose
    //is connected to the 'game_ended' event
    void game_end_UI();

    //toggles visibility of the players own field
    //@TODO make this function available during the turn, wait and init state
    void toggle_home();
};

#endif


/*SEQUENTIEL PROGRESS
 * 1 start of UI with CCStats, CCLog and empty space for battle fields
 * 2 on press on 'R' connect to server
 * 3 ask for server address and port
 * 4 once config received display both battle fields
 * 5 ask for ship placement
 * 6 once it's your turn, call target position to shoot
 * 7 once game ends, call end_game UI with loose or win picture
 *
 *
 */
