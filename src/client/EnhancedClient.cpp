#include "EnhancedClient.h"
#include <boost/log/trivial.hpp>

EnhancedClient::EnhancedClient(){
    visible_home = true;
    initscr();
    int width = getmaxx(stdscr) / 3; 
    int height = getmaxy(stdscr);
    BOOST_LOG_TRIVIAL(debug) << "height: " << height << " \nlogheight: " << height-STATISTIC_HEIGHT;
    //instatiate the 4 main windows
    //furthest right 1st from top
    statistics = std::unique_ptr<CommandCenterStatistics>(new CommandCenterStatistics(STATISTIC_HEIGHT, width, 2*width,0));
    //furthest right 2nd from top
    combat_log = std::unique_ptr<CommandCenterCombatLog>(new CommandCenterCombatLog(height-STATISTIC_HEIGHT-2,width,2*width,STATISTIC_HEIGHT+1));
    //furthest left
    home_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(10,height/3,stdscr));
    //midst window
    enemy_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(width+10,height/3,stdscr));

    BOOST_LOG_TRIVIAL(debug) << "executing constructor...";
}

EnhancedClient::~EnhancedClient(){
}

void EnhancedClient::run(){
    noecho();
    curs_set(0);
    draw_game_ui();
    bool quit = false;

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
                combat_log->log_message("Start positioning your ships");
                set_fleet();
                break;
            case 'r':
                combat_log->log_message("Ready!");
                break;
            default:
                break;
        }
    }
    endwin();
}

void EnhancedClient::set_fleet(){
    bool begin_ship = true;
    bool quit_insert_ship = false;
    int x,y;

    home_field->move_cursor(1,1);
    curs_set(1);
    while(!quit_insert_ship){
        int input = getch();
        x = getcurx(home_field->get_window());
        y = getcury(home_field->get_window());
                        BOOST_LOG_TRIVIAL(debug) << "x: " << x << " y: " << y;
        switch (input){
            case '\n':
                try{
                    position_t start_pos;
                    position_t  end_pos;
                    if(begin_ship){
                        start_pos = home_field->get_position();
                        begin_ship = false;
                    } else {
                        end_pos = home_field->get_position();
                        begin_ship = true;
                        if(!add_ship_to_field(start_pos,end_pos)){
                            combat_log->log_message("An error occured. aborting ship insert modus");
                            //quit_insert_ship = true;
                        }
                    }
                } catch (std::out_of_range &ex){
                    BOOST_LOG_TRIVIAL(error) << ex.what();
                    combat_log->log_message(ex.what());
                }
                break;
            case KEY_RIGHT:
                home_field->move_cursor(++x,y);
                break;
            case KEY_LEFT:
                home_field->move_cursor(--x,y);
                break;
            case KEY_UP:
                home_field->move_cursor(x,--y);
                break;
            case KEY_DOWN:
                home_field->move_cursor(x,++y);
                break;
            case 'q':
                quit_insert_ship = true;
                combat_log->log_message("Fleet is positioned!");
                break;
            default:
                BOOST_LOG_TRIVIAL(debug) << input;
                break;
        }
        wrefresh(home_field->get_window());

    }
    curs_set(0);
}

void EnhancedClient::draw_game_ui(){
    home_field->draw_content();
    enemy_field->draw_content();
    statistics->print_ships(home_field->get_players_battle_field());
}

bool EnhancedClient::add_ship_to_field(position_t start_pos, position_t end_pos){
    if(start_pos == end_pos){
        return false;
    }
    int length = 0;
    orientation_t orientation;
    if(start_pos.x == end_pos.x){
        length = (end_pos.y - start_pos.y)+1;
        orientation = ORIENTATION_VERTICAL;
        if(length < 0){
            length = length * -1;
        }
    } else if (start_pos.y == end_pos.y){
        //@TODO fix the calculation of ship length
        length = (end_pos.x - start_pos.x)/2+1;
        orientation = ORIENTATION_HORIZONTAL;
        if(length < 0){
            length = length * -1;
        }
    }
    BOOST_LOG_TRIVIAL(debug) << "sx: " << start_pos.x << " sy: " << start_pos.y;
    BOOST_LOG_TRIVIAL(debug) << "ex: " << end_pos.x << " ey: " << end_pos.y;
    BOOST_LOG_TRIVIAL(debug) << "length: " << length;
    try{
    home_field->get_player().get_battle_field().add_ship(length,orientation,start_pos);
    } catch (std::out_of_range &ex){
        BOOST_LOG_TRIVIAL(error) << ex.what();
        return false;
    } catch (std::invalid_argument &ex){
        BOOST_LOG_TRIVIAL(error) << ex.what();
        return false;
    }
    BOOST_LOG_TRIVIAL(info) << "A ship has been added";
    combat_log->log_message("the ship has been added");
    return true;
}

void EnhancedClient::toggle_home(){
    home_field->toggle_field_visibility(visible_home);
    visible_home = !visible_home;
}
