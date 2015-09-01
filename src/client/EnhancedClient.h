#ifndef ENHANCEDCLIENT_H
#define ENHANCEDCLIENT_H

#include <clientlib/Player.h>
#include <clientlib/ServerNetworkPackage.h>
#include "BattleFieldUI.h"
#include "CommandCenterStatistics.h"
#include "CommandCenterCombatLog.h"

#define STATISTIC_HEIGHT 14

class EnhancedClient{

private:
    std::unique_ptr<BattleFieldUI> home_field;
    std::unique_ptr<BattleFieldUI> enemy_field;

    std::unique_ptr<CommandCenterStatistics> statistics;
    std::unique_ptr<CommandCenterCombatLog> combat_log;

    bool visible_home;
public:
    EnhancedClient();
    virtual ~EnhancedClient();
    void run();
private:
    void set_fleet();
    void toggle_home();
    void draw_game_ui();
    void add_ship_to_field(int first_x, int first_y, int second_x, int second_y);
};

#endif
