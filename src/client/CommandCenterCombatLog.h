#ifndef _COMMANDCENTER_H
#define _COMMANDCENTER_H

#include <ncurses.h>
#include <string>

#define STATISTIC_HEIGHT 7
class CommandCenter : CursesWindow{
    public:
        CommandCenter(int height, int width, int x, int y);
        virtual ~CommandCenter();
        void write_message(std::string message);
};
#endif
