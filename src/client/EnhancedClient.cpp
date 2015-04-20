#include "EnhancedClient.h"

EnhancedClient::EnhancedClient(){
    battle_field = you.get_battle_field();

}

void EnhancedClient::run(){
    while((input = getstr()) != "q"){
        if(input == "set_fleet"){
            this->set_fleet();
        }
    }
}

void EnhancedClient::set_fleet(){
    if(direction == "UP" || direction == "DOWN" || direction == "LEFT" || direction == "RIGHT"){
        move_pointer();
    } else if (direction == "ENTER"){
        int first_x,first_y,sec_x,sec_y;
        if(begin_ship){
            first_x = getcurx();
            first_y = getcury();
        } else {
            sec_x = getcurx();
            sec_y = getcury();
            //continue with ship add process
            if(sec_y == first_y && sec_x
}

void move_pointer(){
    int y,x;
    WINDOW *win = battle_field_ui.get_home_win();

    getyx(win,y,x);
    if(direction == "UP"){
        y++;
    } else if (direction == "DOWN"){
        y--;
    } else if (direction == "LEFT"){
        x--;
    } else if (direction == "RIGHT"){
        x++;
    }
    move(win,y,x);
}
