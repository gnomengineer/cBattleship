#ifndef _GAMEUI_H
#define _GAMEUI_H

#include <common/BattleField.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string>

class GameUI {
    private:
        BattleFieldUI home_field;
        BattleFieldUI enemy_field;
        CommandCenter command_center;
WINDOW *home_win;
WINDOW *enemy_win;
WINDOW *message_win;
bool is_home_shown = false;
bool is_enemy_shown = false;
    public:
        GameUI();
        virtual ~GameUI();
        void buildup_gameboard();
        BattleFieldUI get_home_field();
        BattleFieldUI get_enemy_field();
        CommandCenter get_command_center();
void hide_field(BattleField home_content);
void draw_home_field(BattleField field);
void draw_enemy_field(BattleField field);
void draw_hit_mark(WINDOW *win, position_t position, bool is_ship);
void show_field(BattleField home_content);
void draw_available_ships(BattleField field);
void write_message(std::string message);
//getter method
WINDOW *get_home_win();
WINDOW *get_enemy_win();
WINDOW *get_message_win();
    private:
void draw_field(WINDOW *win,BattleField field);
};
#endif
