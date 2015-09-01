#include "BattleFieldUI.h"
#include <boost/log/trivial.hpp>

BattleFieldUI::BattleFieldUI(int x, int y, WINDOW *parent) :
    CursesWindow(x,y,2*BATTLEFIELD_HEIGHT,2*BATTLEFIELD_WIDTH,parent)
{
    this->set_scroll(false);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    this->set_attributes(COLOR_PAIR(2));
}

BattleFieldUI::~BattleFieldUI(){

}

void BattleFieldUI::draw_content(){
    this->create_box(0,1);
    int y, x = 0;
    std::vector<std::vector<unsigned char>> field_vector = player.get_battle_field().to_vector(false);

    for(auto field_vector_itr = field_vector.begin(); field_vector_itr != field_vector.end(); ++field_vector_itr){
        for(auto char_itr = field_vector_itr->begin(); char_itr != field_vector_itr->end(); ++char_itr){
            mvwaddch(this->window,y,x+=2,'~');
        }
        y+=2;
    }
    wrefresh(this->window);    
}

void BattleFieldUI::draw_hit_mark(bool isShip,position_t position){
    char character = isShip ? '#' : 'X';
    mvwaddch(this->window,position.y,position.x,character);
    wrefresh(this->window);
}

void BattleFieldUI::toggle_field_visibility(bool visible_flag){
    if(visible_flag){
        this->set_attributes(COLOR_PAIR(2));
    } else {
        this->set_attributes(COLOR_PAIR(1));
    }
    draw_content();
}

Player& BattleFieldUI::get_player(){
    return player;
}
