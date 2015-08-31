#include "EnhancedClient.h"
#include <boost/log/trivial.hpp>

EnhancedClient::EnhancedClient(){
    visible_home = true;
    initscr();
    int width = getmaxx(stdscr) / 3; 

    //instatiate the 4 main windows
    //furthest right 1st from top
    statistics = std::unique_ptr<CommandCenterStatistics>(new CommandCenterStatistics(CommandCenterStatistics.STATISTIC_HEIGHT, width, 2*width,0));
    //furthest right 2nd from top
    combat_log = std::unique_ptr<CommandCenterCombatLog>(new CommandCenterCombatLog());
    //furthest left
    home_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(0,0,stdscr));
    //midst window
    enemy_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(2*BattleField.BATTLEFIELD_HEIGHT,0,stdscr);


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
                break;
            case 'q':
                quit = true;
                break;
            case 'i':
                set_fleet();
                break;
            default:
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
                int first_x,first_y,second_x,second_y;
                if(begin_ship){
                    begin_ship = false;
                    first_x = x;
                    first_y = y;
                } else {
                    begin_ship = true;
                    second_x = x;
                    second_y = y;
                    //continue with ship add process
                    add_ship_to_field(first_x,first_y,second_x,second_y);
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

void EnhancedClient::draw_game_ui(){
    BOOST_LOG_TRIVIAL(debug) << "The UI has been drawn";
}

void EnhancedClient::add_ship_to_field(int first_x,int first_y,int second_x,int second_y){
    BOOST_LOG_TRIVIAL(debug) << "A ship has been added";
}

void EnhancedClient::toggle_home(){
    home_field.toggle_visibility(visible_home);
    visible_home = !visible_home;
}
