#ifndef _CURSESWINDOW_H
#define _CURSESWINDOW_H

#include <ncurses.h>

class CursesWindow{
    protected:
        WINDOW *window;
    public:
        CursesWindow(int x, int y, int height, int width, WINDOW *parent);
        virtual ~CursesWindow();
        void set_scroll(bool status);
        void move_cursor(int x, int y);
};
#endif

