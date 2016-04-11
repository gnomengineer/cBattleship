#include "CursesWindow.h"

CursesWindow::CursesWindow(int x, int y, int height, int width, WINDOW *parent){
    window = derwin(parent,height,width,y,x);

    init_pair(1,COLOR_BLACK,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_GREEN,COLOR_BLACK);
 
}

CursesWindow::~CursesWindow(){

}

void CursesWindow::set_scroll(bool status){
    scrollok(window,status);
}

void CursesWindow::move_cursor(int x, int y){
    wmove(window,y,x);
}

void CursesWindow::set_attributes(int attributes){
    wattron(window,attributes);
}

WINDOW* CursesWindow::get_window(){
    return window;
}

void CursesWindow::create_box(int top,int side){
    box(window,top,side);
}

void CursesWindow::update()
{
    wrefresh(window);
}
