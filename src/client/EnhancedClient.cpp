#include "EnhancedClient.h"

EnhancedClient::EnhancedClient(){
    battle_field = you.get_battle_field();

}

void EnhancedClient::run(){
    while(1){
        int c = getch();
        switch(c){
            case KEY_LEFT:
                battle_field_ui.write_message("Left key pressed");
                break;
            default:
                battle_field_ui.write_message("nothing important");
        }
    }
}

void EnhancedClient::set_fleet(){
    bool begin_ship = true;
    if(direction == "UP" || direction == "DOWN" || direction == "LEFT" || direction == "RIGHT"){
        move_curser();
    } else if (direction == "ENTER"){
        int first_x,first_y,sec_x,sec_y;
        if(begin_ship){
            begin_ship = !begin_ship;
            //first_x = getcurx();
            //first_y = getcury();
        } else {
            begin_ship = !begin_ship;
            //sec_x = getcurx();
            //sec_y = getcury();
            //continue with ship add process
        }
    }
}

void EnhancedClient::move_curser(){
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
    wmove(win,y,x);
}
