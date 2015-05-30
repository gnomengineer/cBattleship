#include "CommandCenter.h"

CommandCenter::CommandCenter(int height, int width, int x, int y) : CursesWindow(x,y,height,width,stdscr)
{

}

CommandCenter::~CommandCenter(){

}

float CommandCenter::calculate_hit_rate(){
    return this.hits / this.shots;
}

void CommandCenter::increase_shot(bool is_hit){
    ++this.shots;
    if(is_hit)
        ++this.hits;
}

void CommandCenter::print_ships(BattleField &battle_field,int attrs_number, int attrs_text){
    std::map<unsigned int, int> ship_list = battle_field->get_ships_available();
    std::string ship_names[] = {"Cruiser","Destroyer","Battleship","Aircraft Carrier"};
    int y = 1;
    for(auto iterator = ship_list.begin(); iterator != ship_list.end(); ++iterator){
        wattron(window,attrs_text);
        mvwprintw(window,y++,3,"%s x", ship_names[itr->first - 2].c_str());
        wattron(window,attrs_number);
        wprintw(window, "%i", itr->second);
    }

    mvwprintw(window,y++,3,"hit ratio: %.2i", calculate_hit_rate());
    wrefresh(window);
}
