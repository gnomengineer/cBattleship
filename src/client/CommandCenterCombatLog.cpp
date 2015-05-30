#include "CommandCenterCombatLog.h"

CommandCenter::CommandCenter(int height, int width, int x, int y) : CursesWindow(x,y,height,width,stdscr){
    this->set_scroll(true);
}

CommandCenter::~CommandCenter(){

}

void CommandCenter::write_message(std::string message){
    int y = getcury(game_progress_window)+1;
    mvwprintw(game_progress_window,y,3 "%s", message.c_str());
    wrefresh(game_progress_window);
}
