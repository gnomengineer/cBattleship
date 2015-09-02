#include "BattleFieldUI.h"

BattleFieldUI::BattleFieldUI(int x, int y, WINDOW *parent) :
    CursesWindow(x,y,BATTLEFIELD_HEIGHT+1,2*BATTLEFIELD_WIDTH,parent)
{
    this->set_scroll(false);
    start_color();
    this->set_attributes(COLOR_PAIR(GREEN));
    this->create_box(0,1);
    this->set_attributes(COLOR_PAIR(BLUE));

}

BattleFieldUI::~BattleFieldUI(){

}

void BattleFieldUI::draw_content(){
    int y = 1;
    int x = 0;
    std::vector<std::vector<unsigned char>> field_vector = player.get_battle_field().to_vector(false);

    for(auto field_vector_itr = field_vector.begin(); field_vector_itr != field_vector.end(); ++field_vector_itr){
        for(auto char_itr = field_vector_itr->begin(); char_itr != field_vector_itr->end(); ++char_itr){
            mvwaddch(this->window,y,x+=2,'~');
        }
        y++;
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
        this->set_attributes(COLOR_PAIR(BLUE));
    } else {
        this->set_attributes(COLOR_PAIR(BLACK));
    }
    draw_content();
}

Player& BattleFieldUI::get_player(){
    return player;
}

BattleField& BattleFieldUI::get_players_battle_field(){
    return player.get_battle_field();
}

position_t BattleFieldUI::get_position(){
    int x = getcurx(window);
    int y = getcury(window);
    if(x%2 == 0 && x > 0 && y != 0){
        x = (x-2)/2;
        y -= 1;
    } else {
        throw std::out_of_range("you selected an invalid position");
    }

    position_t position;
    position.x = x;
    position.y = y;

    return position;
}
