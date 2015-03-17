#ifndef _BATTLEFIELDUI_H
#define _BATTLEFIELDUI_H

#include <common/BattleField.h>
#include <ncurses.h>
#include <stdlib.h>

class BattleFieldUI {
    private:
WINDOW *home_win;
BattleField home_content;
WINDOW *enemy_win;
BattleField enemy_content;
bool is_home_shown = false;
bool is_enemy_shown = false;
    public:
BattleFieldUI();
void hide_field();
void draw_field(WINDOW *win);
void draw_hit_mark(WINDOW *win, position_t position, bool is_ship);
void show_field(WINDOW *win);
//getter method
WINDOW get_home_win();
WINDOW get_enemy_win();
};
#endif
