#ifndef _BATTLEFIELDUI_H
#define _BATTLEFIELDUI_H

#include <common/BattleField.h>
#include <ncurses.h>
#include <stdlib.h>

typedef enum{
    SHIP = 0,
    EMPTY = 1,
    SHIP_Hit = 2,
    MISS = 3
} graphic_content;

class BattleFieldUI {
    private:
WINDOW *home_win;
char home_content[BATTLEFIELD_HEIGHT][BATTLEFIELD_WIDTH] ;
WINDOW *enemy_win;
char enemy_content[BATTLEFIELD_HEIGHT][BATTLEFIELD_WIDTH] ;
    public:
BattleFieldUI();
void hide_field(WINDOW *win);
void draw_field();
void draw_ship(int length, int orientation, position_t position);
void draw_hit_mark(WINDOW *win, position_t position, bool is_ship);
void show_field(WINDOW *win);
};
#endif
