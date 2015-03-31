#include "BattleFieldUI.h"
#include "Log.h"

BattleFieldUI::BattleFieldUI(){
    initscr();
    box(stdscr,0,0);
    start_color();
    curs_set(1);
    
    //define normal COLOR_PAIR
    init_pair(1, COLOR_BLUE,COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);


    home_win = derwin(stdscr,BATTLEFIELD_HEIGHT,BATTLEFIELD_WIDTH, 1, 2);
    box(home_win,0,0);
    enemy_win = derwin(stdscr,BATTLEFIELD_HEIGHT,BATTLEFIELD_WIDTH, 1, BATTLEFIELD_WIDTH + 3);
    box(enemy_win,0,0);

}

BattleFieldUI::~BattleFieldUI(){
    getch();
    endwin();
}

void BattleFieldUI::hide_field(BattleField home_content){
    wcolor_set(home_win, COLOR_PAIR(2),NULL);
    draw_field(home_win,home_content);
    wcolor_set(home_win, COLOR_PAIR(1),NULL);
}

void BattleFieldUI::draw_field(WINDOW *win, BattleField field){
    std::vector<std::vector<unsigned char>> field_vector = field.to_vector(false);
    int y = 0;
    for(auto field_vector_itr = field_vector.begin(); field_vector_itr != field_vector.end(); ++field_vector_itr){
        y++;
        int x = 0;
        for(auto itr = field_vector_itr->begin(); itr != field_vector_itr->end(); ++itr){
            mvwaddch(win,y,x++,ACS_BLOCK);
        }
        logfile << y << "," << x << std::endl;
    }   
    logfile << BATTLEFIELD_WIDTH << BATTLEFIELD_HEIGHT << std::endl;
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
    if(is_ship){
        mvwaddch(win,position.y,position.x,'#');
    } else {
        mvwaddch(win,position.y,position.x,'X');
    }
}

void BattleFieldUI::show_field(WINDOW *win){
    
}

WINDOW* BattleFieldUI::get_home_win(){
    return this->home_win;
}

WINDOW* BattleFieldUI::get_enemy_win(){
    return this->enemy_win;
}
