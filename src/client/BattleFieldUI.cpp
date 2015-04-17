#include "BattleFieldUI.h"
#include "Log.h"

BattleFieldUI::BattleFieldUI(){
    initscr();
    start_color();
    curs_set(1);
    
    //define normal COLOR_PAIR
    init_pair(1, COLOR_BLUE,COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    home_win = derwin(stdscr,2*BATTLEFIELD_HEIGHT+1,2*BATTLEFIELD_WIDTH+1, 2, 2);
    enemy_win = derwin(stdscr,2*BATTLEFIELD_HEIGHT+1,2*BATTLEFIELD_WIDTH+1, 2, 2*BATTLEFIELD_WIDTH + 6);
    box(enemy_win,0,0);
    box(home_win,0,0);

}

BattleFieldUI::~BattleFieldUI(){
    getch();
    endwin();
}

void BattleFieldUI::hide_field(BattleField home_content){
    wattron(home_win,COLOR_PAIR(2));
    draw_field(home_win,home_content);
    wrefresh(home_win);
    refresh();
}

void BattleFieldUI::draw_field(WINDOW *win, BattleField field){
    std::vector<std::vector<unsigned char>> field_vector = field.to_vector(false);
    int y = 1;
    for(auto field_vector_itr = field_vector.begin(); field_vector_itr != field_vector.end(); ++field_vector_itr){
        int x = 1;
        for(auto itr = field_vector_itr->begin(); itr != field_vector_itr->end(); ++itr){
            mvwaddch(win,y,x,'~');
            x += 2;
        }
        y+=2;
    }   
    wrefresh(win);
    refresh();
}

void BattleFieldUI::draw_home_field(BattleField field){
    this->draw_field(home_win,field);
}

void BattleFieldUI::draw_enemy_field(BattleField field){
    this->draw_field(enemy_win,field);
}

void BattleFieldUI::draw_hit_mark(WINDOW *win, position_t position, bool is_ship){
    wattroff(win,COLOR_PAIR(1));
    wattron(win,COLOR_PAIR(3));
    if(is_ship){
        mvwaddch(win,position.y+2,position.x+2,'#');
    } else {
        mvwaddch(win,position.y+2,position.x+2,'X');
    }
    refresh();
    wrefresh(win);
}

void BattleFieldUI::show_field(BattleField home_content){
    wattron(home_win,COLOR_PAIR(1)); 
    draw_field(home_win,home_content);
    wrefresh(home_win);
    refresh();
}

WINDOW* BattleFieldUI::get_home_win(){
    return this->home_win;
}

WINDOW* BattleFieldUI::get_enemy_win(){
    return this->enemy_win;
}
