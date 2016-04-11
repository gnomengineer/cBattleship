#ifndef _CURSESWINDOW_H
#define _CURSESWINDOW_H

#include <ncurses.h>

#define RED 3
#define GREEN 4
#define BLUE 2
#define BLACK 1

class CursesWindow{
    protected:
        WINDOW *window;
    public:
        CursesWindow(int x, int y, int height, int width, WINDOW *parent);
        virtual ~CursesWindow();
        void set_scroll(bool status);
        void move_cursor(int x, int y);
        void set_attributes(int attributes);
        void create_box(int side, int top);
        WINDOW *get_window();
        void update();
};
#endif

