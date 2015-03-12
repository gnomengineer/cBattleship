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
    std::vector<unsigned char> home_char = home_content.to_vector(false);
    int y = 0;
    for(int i = 0; i < home_char.length(); i++){
        if(i % BATTLEFIELD_WIDTH == 0)
            y++;
    }   
}

void BattleFieldUI::draw_hit_mark(WINDOW *win, position_t position, bool is_ship){

}

void BattleFieldUI::show_field(WINDOW *win){

}
