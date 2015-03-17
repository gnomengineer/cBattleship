#include "BattleFieldUI.h"

BattleFieldUI::BattleFieldUI(){
    initscr();
    start_color();
    curs_set(1);
    
    //define normal COLOR_PAIR
    init_pair(1, COLOR_BLUE,COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_parr(4, COLOR_GREEN, COLOR_Black);

    home_content

    home_win = subwin(stdscr,BATTLEFIELD_HEIGHT,BATTLEFIELD_WIDTH, 10, 20);
    enemy_win = subwin(stdscr,BATTLEFIELD_HEIGHT,BATTLEFIELD_WIDTH, 10, BATTLEFIELD_WIDTH + 30);

}

void BattleFieldUI::hide_field(){
    wcolor_set(home_win, COLOR_PAIR(2));
    draw_field(home_win,home_content);
    wcolor_set(home_win, COLOR_PAIR(1));
}

void BattleFieldUI::draw_field(WINDOW *win, BattleField field){
    std::vector<std::vector<unsigned char>> field_vector = field.to_vector(false);
    int y = 0;
    for(auto field_vector_itr = field_vector.begin(); field_vector_itr != field_vector.end(); field_vector_itr++){
        y++;
        int x = 0;
        for(auto itr = field_vector_itr.begin(); itr != field_vector_itr.end(); itr++){
            mvwaddch(win,y,x++,itr);
        }
    }   
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

WINDOW get_home_win(){
    return home_win;
}

WINDOW get_enemy_win(){
    return enemy_win;
}
