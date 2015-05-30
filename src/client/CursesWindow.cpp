#include "CursesWindow.h"

CursesWindow::CursesWindow(int x, int y, int height, int width, WINDOW *parent){
    window = derwin(parent,height,width,x,y);
}

CursesWindow::~CursesWindow(){

}

void CursesWindow::set_scroll(bool status){
    scrollok(window,status);
}

void CursesWindow::move_cursor(int x, int y){
    wmove(window,x,y);
}

