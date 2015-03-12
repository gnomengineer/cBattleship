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
    public:
BattleFieldUI();
void hide_field(WINDOW *win);
void draw_field();
void draw_hit_mark(WINDOW *win, position_t position, bool is_ship);
void show_field(WINDOW *win);
};
#endif
