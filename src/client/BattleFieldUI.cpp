#include "BattleFieldUI.h"

BattleFieldUI::BattleFieldUI(){
    initscr();
    curs_set(1);
    

    home_win = subwin(stdscr,BattleField.BATTLEFIELD_HEIGHT,BattleField.BATTLEFIELD_WIDTH, 10, 20);
    enemy_win = subwin(stdscr,BattleField.BATTLEFIELD_HEIGHT,BattleField.BATTLEFIELD_WIDTH, 10, BattleField.BATTLEFIELD_WIDTH + 30);

}

void BattleFieldUI::hide_field(WINDOW *win){

}

void BattleFieldUI::draw_field(){
    
}

void BattleFieldUI::draw_ship(int length, int orientation, pos_t position){

}

void BattleFieldUI::draw_hit_mark(WINDOW *win, pos_t position, bool is_ship){

}

void BattleFieldUI::show_field(WINDOW *win){

}
