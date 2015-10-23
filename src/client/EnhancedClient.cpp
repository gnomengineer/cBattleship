#include "EnhancedClient.h"
#include <boost/log/trivial.hpp>
#include <sstream>

EnhancedClient::EnhancedClient(){
    
    visible_home = true;
    initscr();
    int width = getmaxx(stdscr) / 3; 
    int height = getmaxy(stdscr);

    //instatiate the 4 main windows
    //furthest right 1st from top
    statistics = std::unique_ptr<CommandCenterStatistics>(new CommandCenterStatistics(STATISTIC_HEIGHT, width, 2*width,0));
    //furthest right 2nd from top
    combat_log = std::unique_ptr<CommandCenterCombatLog>(new CommandCenterCombatLog(height-STATISTIC_HEIGHT-2,width,2*width,STATISTIC_HEIGHT+1));
    //furthest left
    home_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(10,height/3,stdscr));
    mvprintw(height/3-1,10,"YOUR FIELD");
    //midst window
    enemy_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(width+10,height/3,stdscr));
    mvprintw(height/3-1,width+10,"ENEMY FIELD");
}

EnhancedClient::~EnhancedClient(){
}

void EnhancedClient::setup() {
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
                //ask for connection string
                //check connection string
                //std::string connection_string = "";
                combat_log->log_message("Ready!");
                //run(connection_string);
                break;
            case 'v':
                home_field->toggle_field_visibility(visible_home);
                visible_home = !visible_home;
                home_field->draw_content();
                break;
            default:
                break;
        }
    }
    endwin();
}

void EnhancedClient::run(std::string connection_string){
    //connect to server
    //
    //while connected stay
    //
    //set curses focus on enemy_field
    //
    //if 'v' set home visible
    //if 'enter' and your turn send shot
    //if not your turn wait
    //if 'q' disconnect
    //
    //update field according to turn result
    bool quit_connection = false;
    

    while(!quit_connection){
        
    }
}

void EnhancedClient::set_fleet(){
    bool begin_ship = true;
    bool quit_insert_ship = false;
    int x,y;

    position_t start_pos;
    position_t  end_pos;
    std::string positions;

    home_field->move_cursor(1,1);
    curs_set(1);
    while(!quit_insert_ship){
        int input = getch();
        x = getcurx(home_field->get_window());
        y = getcury(home_field->get_window());
        switch (input){
            case '\n':
                try{
                    if(begin_ship){
                        start_pos = home_field->get_position();
                        begin_ship = false;
                        std::stringstream ss;
                        ss << "start position x: " << start_pos.x << " y: " << start_pos.y;
                        combat_log->log_message(ss.str());
                    } else {
                        end_pos = home_field->get_position();
                        begin_ship = true;
                        std::stringstream ss;
                        ss << "end position x: " << end_pos.x << " y: " << end_pos.y;
                        combat_log->log_message(ss.str());
                        add_ship_to_field(start_pos,end_pos);
                        home_field->draw_content();
                        statistics->print_ships(home_field->get_player().get_battle_field());
                        //@TODO make a message if every possible ship is set
                        if(home_field->get_player().get_battle_field().get_ships_available().size() == 0){
                            quit_insert_ship = true;
                            combat_log->log_message("You can't place any more ships. Leaving ship insert mode.");
                        }
                    }
                } catch (std::out_of_range &ex){
                    BOOST_LOG_TRIVIAL(error) << ex.what();
                    combat_log->log_message(ex.what());
                } catch (std::invalid_argument &ex){
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

void EnhancedClient::add_ship_to_field(position_t start_pos, position_t end_pos){
    int length = 0;
    orientation_t orientation;
    if(start_pos.x == end_pos.x){
        length = end_pos.y - start_pos.y;
        orientation = ORIENTATION_VERTICAL;
    } else if (start_pos.y == end_pos.y){
        length = end_pos.x - start_pos.x ;
        orientation = ORIENTATION_HORIZONTAL;
    }

    if(length < 0){
        int x = start_pos.x;
        int y = start_pos.y;
        start_pos.x = end_pos.x;
        start_pos.y = end_pos.y;
        end_pos.y = y;
        end_pos.x = x;
        length = length * -1;
    }
    length += 1;

    home_field->get_player().get_battle_field().add_ship(length,orientation,start_pos);

    BOOST_LOG_TRIVIAL(info) << "A ship has been added";
    std::stringstream log_msg;
    log_msg << "the ship of length " << length << " has been added";
    combat_log->log_message(log_msg.str());
}

void EnhancedClient::toggle_home(){
    home_field->toggle_field_visibility(visible_home);
    visible_home = !visible_home;
}
