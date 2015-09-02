#include "CommandCenterCombatLog.h"

CommandCenterCombatLog::CommandCenterCombatLog(int height, int width, int x, int y) : CursesWindow(x,y,height,width,stdscr){
    this->set_scroll(true);
    this->set_attributes(COLOR_PAIR(GREEN));
    this->create_box(1,0);
}

CommandCenterCombatLog::~CommandCenterCombatLog(){

}

void CommandCenterCombatLog::log_message(std::string message){
    this->set_attributes(COLOR_PAIR(RED));
    int y = getcury(this->window)+1;
    mvwprintw(this->window,y,3, "%s", message.c_str());
    wrefresh(this->window);
}
