#include "BattleFieldUI.h"
#include "Log.h"

BattleFieldUI::BattleFieldUI(){
    initscr();
    start_color();
    
    //define normal COLOR_PAIR
    init_pair(1, COLOR_BLUE,COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(4));
    int width =  2* BATTLEFIELD_HEIGHT+1;
    int height = width;
    if(getmaxx(stdscr) / 3 > width)
        width = getmaxx(stdscr) / 3;
    if(getmaxy(stdscr) > height)
        height = getmaxy(stdscr) - 5 ;

    home_win = derwin(stdscr,height,width, 2, 0);
    enemy_win = derwin(stdscr,height,width, 2, width);
    message_win = derwin(stdscr,height,width, 2, 2*width);
    //boxing the windows
    box(home_win,0,1);
    box(enemy_win,0,1);
    box(message_win,1,0);
    //name the windows
    std::string win_text[] = {"YOUR FIELD","ENEMEY FIELD", "COMMAND CENTER"};
    mvwprintw(home_win,1,(getmaxx(home_win)-win_text[0].length())/2, "%s", win_text[0].c_str());
    mvwprintw(enemy_win,1,(getmaxx(enemy_win)-win_text[1].length())/2,"%s", win_text[1].c_str());
    mvwprintw(message_win,1,(getmaxx(message_win)-win_text[2].length())/2, "%s", win_text[2].c_str());

}

BattleFieldUI::~BattleFieldUI(){
    getch();
    endwin();
}

void BattleFieldUI::hide_field(BattleField home_content){
    wattron(home_win,COLOR_PAIR(2));
    draw_field(home_win,home_content);
    wrefresh(home_win);
}

void BattleFieldUI::draw_field(WINDOW *win, BattleField field){
    std::vector<std::vector<unsigned char>> field_vector = field.to_vector(false);
    int counter_y = 0; //counter for naming y-axis
    int y = (getmaxy(win) - 2*BATTLEFIELD_HEIGHT) / 2;
    //set color_attribute and printing naming of vertical axis
    wattron(win, COLOR_PAIR(1));
    //write name of y-axis to screen
    mvwaddch(win,getmaxy(win)/2-2,(getmaxx(win) - 2*BATTLEFIELD_WIDTH) /2-6,'y');

    for(auto field_vector_itr = field_vector.begin(); field_vector_itr != field_vector.end(); ++field_vector_itr){
        int counter_x = 0; //counter for naming x-axis
        int x = (getmaxx(win) - 2*BATTLEFIELD_WIDTH) /2;
        //print y numbers on screen
        mvwprintw(win,y,x-4,"%i",counter_y++);

        for(auto itr = field_vector_itr->begin(); itr != field_vector_itr->end(); ++itr){
            if(y == (getmaxy(win) - 2*BATTLEFIELD_HEIGHT)/2){
                //only on first row, print name and numbers of x-axis
                mvwaddch(win, y -4, getmaxx(win)/2, 'x');
                mvwprintw(win, y -2, x, "%i", counter_x++);
            }

            mvwaddch(win,y,x,'~');
            x += 2;
        }
        y+=2;
    }   
    wrefresh(win);
}

void BattleFieldUI::draw_home_field(BattleField field){
    this->draw_field(home_win,field);
}

void BattleFieldUI::draw_enemy_field(BattleField field){
    this->draw_field(enemy_win,field);
}

void BattleFieldUI::draw_hit_mark(WINDOW *win, position_t position, bool is_ship){
    wattron(win,COLOR_PAIR(3));
    if(is_ship){
        mvwaddch(win,position.y+2,position.x+2,'#');
    } else {
        mvwaddch(win,position.y+2,position.x+2,'X');
    }
    wrefresh(win);
}

void BattleFieldUI::show_field(BattleField home_content){
    wattron(home_win,COLOR_PAIR(1)); 
    draw_field(home_win,home_content);
    wrefresh(home_win);
    refresh();
}

void BattleFieldUI::draw_available_ships(BattleField field){
    int y = 5;
    std::map<unsigned int, int> ship_list = field.get_ships_available();
    std::string ship_names[] = {"Cruiser", "Destroyer","Battleship","Aircraft Carrier"};
    for(auto itr = ship_list.begin(); itr != ship_list.end(); itr++){
        wattron(message_win, COLOR_PAIR(4));
        mvwprintw(message_win,y++,3,"%s x", ship_names[itr->first - 2].c_str());
        wattron(message_win,COLOR_PAIR(3));
        wprintw(message_win,"%i", itr->second);
    }
    wrefresh(message_win);
}

void BattleFieldUI::write_message(std::string message){
    wprintw(message_win, "%s", message.c_str());
}

WINDOW* BattleFieldUI::get_home_win(){
    return this->home_win;
}

WINDOW* BattleFieldUI::get_enemy_win(){
    return this->enemy_win;
}

WINDOW* BattleFieldUI::get_message_win(){
    return this->message_win;
}
