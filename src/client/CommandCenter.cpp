#include "CommandCenter.h"

CommandCenter::CommandCenter(int height,int width){
    game_statistics_window = derwin(stdscr,height,width,0,0);
    game_progress_window = derwin(stdscr,height - STATISTIC_HEIGHT,width,0+STATISTICS_HEIGHT,0);
    scrollok(game_progress_window,true);
}

CommandCenter::~CommandCenter(){

}

float CommandCenter::calculate_hit_rate(){
    return this.hits / this.shots;
}

void CommandCenter::write_message(std::string message){
    int y = getcury(game_progress_window)+1;
    mvwprintw(game_progress_window,y,3 "%s", message.c_str());
    wrefresh(game_progress_window);
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
        wattron(game_statistics_window,attrs_text);
        mvwprintw(game_statistics_window,y++,3,"%s x", ship_names[itr->first - 2].c_str());
        wattron(game_statistics_window,attrs_number);
        wprintw(game_statistics_window, "%i", itr->second);
    }

    mvwprintw(game_statistics_window,y++,3,"hit ratio: %.2i", calculate_hit_rate());
    wrefresh(game_statistics_window);
}
