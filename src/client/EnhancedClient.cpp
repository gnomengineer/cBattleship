#include "EnhancedClient.h"
#include <boost/log/trivial.hpp>

EnhancedClient::EnhancedClient(){
    home_field = you.get_battle_field();
    enemy_field = enemy.get_battle_field();

}

EnhancedClient::~EnhancedClient(){
}

void EnhancedClient::run(){
    noecho();
    curs_set(0);
    draw_game_ui();
    bool quit = false;

    BOOST_LOG_TRIVIAL(debug) << "test";
    keypad(stdscr,true);
    while(!quit){
        int c = getch();
        switch(c){
            case KEY_UP:
                battle_field_ui.write_message("Left key pressed");
                break;
            case 'q':
                quit = true;
                break;
            case 'i':
                battle_field_ui.write_message("Now set your fleet!");
                set_fleet();
                break;
            default:
                battle_field_ui.write_message("nothing important");
        }
    }
}

void EnhancedClient::set_fleet(){
    bool begin_ship = true;
    bool quit_insert_ship = false;
    int x,y;

    WINDOW *win = battle_field_ui.get_home_win();
    curs_set(1);
    wmove(win,1,1);
    while(!quit_insert_ship){
        int input = getch();
        x = getcurx(win);
        y = getcury(win);
        switch (input){
            case '\n':
                int first_x,first_y,sec_x,sec_y;
                if(begin_ship){
                    begin_ship = false;
                    first_x = x;
                    first_y = y;
                } else {
                    begin_ship = true;
                    sec_x = x;
                    sec_y = y;
                    //continue with ship add process
                }
                break;
            case 'q':
                quit_insert_ship = true;
                battle_field_ui.write_message("Fleet is positioned!");
                break;
            default:
                BOOST_LOG_TRIVIAL(debug) << input;
                move_cursor(win,input,x,y);
                break;
        }

    }
    curs_set(0);
}

void EnhancedClient::move_cursor(WINDOW *win, int direction, int x, int y){
    switch(direction){
        case KEY_UP:
            battle_field_ui.write_message("KEY UP");
            y -= 2;
            break;
        case KEY_DOWN:
            battle_field_ui.write_message("KEY DOWN");
            y += 2;
            break;
        case KEY_LEFT:
            battle_field_ui.write_message("KEY LEFT");
            x -= 2;
            break;
        case KEY_RIGHT:
            battle_field_ui.write_message("KEY RIGHT");
            x += 2;
            break;
        default:
            break;
    }
    wmove(win,y,x);
    wrefresh(win);
}

void EnhancedClient::draw_game_ui(){
    battle_field_ui.draw_enemy_field(enemy_field);
    battle_field_ui.draw_home_field(home_field);
    battle_field_ui.draw_available_ships(home_field);
}
