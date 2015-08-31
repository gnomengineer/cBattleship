#include "BattleFieldUI.h"

BattleFieldUI::BattleFieldUI(int x, int y, WINDOW *parent) :
    CursesWindow(x,y,2*BATTLEFIELD_HEIGHT,2*BATTLEFIELD_WIDTH,parent)
{
    this->set_scroll(false);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
}

BattleFieldUI::~BattleFieldUI(){

}

void BattleFieldUI::draw_content(){
    int y, x = 0;
    std::vector<std::vector<unsigned char>> field_vector = player->get_battle_field()->to_vector(false);

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
        wattron(this->window,COLOR_PAIR(1));
    } else {
        wattron(this->window,COLOR_PAIR(2));
    }
    draw_content();
}

Player &BattleFieldUI::get_player(){
    return player;
}
