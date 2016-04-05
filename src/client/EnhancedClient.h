/** DEPRECATED **/

#ifndef ENHANCEDCLIENT_H
#define ENHANCEDCLIENT_H

#include <clientlib/Player.h>
#include <clientlib/ClientStateMachine.h>
#include "BattleFieldUI.h"
#include "CommandCenterStatistics.h"
#include "CommandCenterCombatLog.h"
#include <common/position.h>

#define STATISTIC_HEIGHT 14

class EnhancedClient{

private:
    std::unique_ptr<BattleFieldUI> home_field;
    std::unique_ptr<BattleFieldUI> enemy_field;

    std::unique_ptr<CommandCenterStatistics> statistics;
    std::unique_ptr<CommandCenterCombatLog> combat_log;

    std::unique_ptr<WinScreen> end_ui;

    ClientStateMachine client_state_machine;

    bool visible_home;
public:
    EnhancedClient();
    virtual ~EnhancedClient();
    void setup();
private:
    void run(std::string connection_string);
    void set_fleet();
    void set_target();
    void toggle_home();
    void draw_game_ui();
    void add_ship_to_field(position_t start_pos, position_t end_pos);
};

#endif
