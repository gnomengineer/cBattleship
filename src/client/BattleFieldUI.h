#ifndef _BATTLEFIELDUI_H
#define _BATTLEFIELDUI_H

#include <common/BattleField.h>
#include <ncurses.h>
#include <stdlib.h>

class BattleFieldUI {
    private:
WINDOW *home_win;
WINDOW *enemy_win;
bool is_home_shown = false;
bool is_enemy_shown = false;
    public:
BattleFieldUI();
virtual ~BattleFieldUI();
void hide_field(BattleField home_content);
void draw_home_field(BattleField field);
void draw_enemy_field(BattleField field);
void draw_field(WINDOW *win,BattleField field);
void draw_hit_mark(WINDOW *win, position_t position, bool is_ship);
void show_field(WINDOW *win);
//getter method
WINDOW *get_home_win();
WINDOW *get_enemy_win();
};
#endif
