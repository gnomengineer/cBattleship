#include "EnhancedClient.h"
#include "Log.h"

EnhancedClient::EnhancedClient(){
    home_field = you.get_battle_field();
    enemy_field = enemy.get_battle_field();

}

EnhancedClient::~EnhancedClient(){
}

void EnhancedClient::run(){
    draw_game_ui();
    bool quit = false;
logfile << "test run" << std::endl;
    while(!quit){
        char c = getch();
        logfile << "input: " << c << std::endl;
        switch(c){
            case 'w':
                battle_field_ui.write_message("Left key pressed");
                break;
            case 'q':
                quit = !quit;
                break;
            case 'i':
                set_fleet();
                break;
            default:
                battle_field_ui.write_message("nothing important");
        }
    }

    endwin();
}

void EnhancedClient::set_fleet(){
    bool begin_ship = true;
    bool quit_insert_ship = false;
    int x,y;

    WINDOW *win = battle_field_ui.get_home_win();
    while(!quit_insert_ship){
        char input = getch();
        x = getcurx(win);
        y = getcury(win);
        switch (input){
            case '\n':
                int first_x,first_y,sec_x,sec_y;
                if(begin_ship){
                    begin_ship = !begin_ship;
                    first_x = x;
                    first_y = y;
                } else {
                    begin_ship = !begin_ship;
                    sec_x = x;
                    sec_y = y;
                    //continue with ship add process
                }
                break;
            case 'm':
                move_cursor(win,input,x,y);
                break;
            case 'q':
                quit_insert_ship = !quit_insert_ship;
                break;
            default:
                logfile << std::endl;
        }

    }
}

void EnhancedClient::move_cursor(WINDOW *win, char direction, int x, int y){
    switch(direction){
        case '1':
            x--;
            break;
        case '2':
            x++;
            break;
        case '3':
            y--;
            break;
        case '4':
            y++;
            break;
        default:
            break;
    }
    wmove(win,y,x);
}

void EnhancedClient::draw_game_ui(){
    battle_field_ui.draw_enemy_field(enemy_field);
    battle_field_ui.draw_home_field(home_field);
    battle_field_ui.draw_available_ships(home_field);
}
