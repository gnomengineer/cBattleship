#include "BattleFieldUI.h"

BattleFieldUI::BattleFieldUI(){
    initscr();
    curs_set(1);
    

    home_win = subwin(stdscr,BATTLEFIELD_HEIGHT,BATTLEFIELD_WIDTH, 10, 20);
    enemy_win = subwin(stdscr,BATTLEFIELD_HEIGHT,BATTLEFIELD_WIDTH, 10, BATTLEFIELD_WIDTH + 30);

}

void BattleFieldUI::hide_field(WINDOW *win){

}

void BattleFieldUI::draw_field(){
    
}

void BattleFieldUI::draw_ship(int length, int orientation, position_t position){

}

void BattleFieldUI::draw_hit_mark(WINDOW *win, position_t position, bool is_ship){

}

void BattleFieldUI::show_field(WINDOW *win){

}
