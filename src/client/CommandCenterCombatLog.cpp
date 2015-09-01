#include "CommandCenterCombatLog.h"

CommandCenterCombatLog::CommandCenterCombatLog(int height, int width, int x, int y) : CursesWindow(x,y,height,width,stdscr){
    this->set_scroll(true);
}

CommandCenterCombatLog::~CommandCenterCombatLog(){

}

void CommandCenterCombatLog::log_message(std::string message){
    int y = getcury(this->window)+1;
    mvwprintw(this->window,y,3, "%s", message.c_str());
    wrefresh(this->window);
}
