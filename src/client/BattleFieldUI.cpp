#include "BattleFieldUI.h"

BattleFieldUI::BattleFieldUI(int x, int y) {
    field_window = derwin(stdscr,BATTLEFIELD_HEIGHT * 2,BATTLEFIELD_WIDTH*2,x,y);
}

BattleFieldUI::~BattleFieldUI(){

}

void BattleFieldUI::move_cursor(int x, int y){
    wmove(field_window,x,y);
}

void BattleFieldUI::draw_content(){
    int y, x = 0;
    std::vector<std::vector<unsigned char>> field_vector = field_info.to_vector(false);
    for(auto field_vector_itr = field_vector.begin(); field_vector_itr != field_vector.end(); ++field_vector_itr){
        for(auto char_itr = field_vector_itr->begin(); char_itr != field_vector_itr->end(); ++char_itr){
            mvwaddch(field_window,y,x+=2,'~');
        }
        y+=2;
    }
    wrefresh(field_window);    
}

void BattleFieldUI::draw_hit_mark(bool isShip,position_t position){
    char character = isShip ? '#' : 'X';
    mvwaddch(field_window,position.y,position.x,character);
    wrefresh(field_window);
}

void BattleFieldUI::toggle_field_visibility(int attrs){
    wattron(field_window,attrs);
    draw_content();
}

BattleField* BattleFieldUI::get_battle_field(){
    return this->field_info;
}

WINDOW* BattleFieldUI::get_window(){
    return this->field_window;
}
