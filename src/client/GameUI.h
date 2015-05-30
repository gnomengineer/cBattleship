#ifndef _GAMEUI_H
#define _GAMEUI_H

#include <common/BattleField.h>
#include "CommandCenterCombatLog.h"
#include "CommandCenterStatistics.h"
#include "BattleFieldUI.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include <memory>

class GameUI {
    private:
        std::unique_ptr<BattleFieldUI> home_field;
        std::unique_ptr<BattleFieldUI> enemy_field;
        std::unique_ptr<CommandCenterCombatLog> cmd_log;
        std::unique_ptr<CommandCenterStatistics> cmd_statistic;
        WINDOW *home_win;
        WINDOW *enemy_win;
bool is_home_shown = false;
bool is_enemy_shown = false;
    public:
        GameUI();
        virtual ~GameUI();
        void buildup_gameboard();
        BattleFieldUI get_home_field();
        BattleFieldUI get_enemy_field();
        CommandCenterCombatLog get_command_log();
        CommandCenterStatistics get_command_statistics();
void hide_field(BattleField home_content);
//getter method
WINDOW *get_home_win();
WINDOW *get_enemy_win();
    private:
void draw_field(WINDOW *win,BattleField field);
};
#endif
