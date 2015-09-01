#ifndef _COMMANDCENTERCOMBATLOG_H
#define _COMMANDCENTERCOMBATLOG_H

#include <ncurses.h>
#include "CursesWindow.h"
#include <string>

class CommandCenterCombatLog : public CursesWindow{
    public:
        CommandCenterCombatLog(int height, int width, int x, int y);
        virtual ~CommandCenterCombatLog();
        void log_message(std::string message);
};
#endif
