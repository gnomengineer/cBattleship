#include "GameUI.h"

GameUI::GameUI(){
    initscr();
    start_color();
    
    //define normal COLOR_PAIR
    init_pair(1, COLOR_BLUE,COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(4));

    home_win = derwin(stdscr,height,width, 2, 0);
    enemy_win = derwin(stdscr,height,width, 2, width);
    //boxing the windows
    box(home_win,0,1);
    box(enemy_win,0,1);
    //name the windows
   
    mvwprintw(home_win,1,(getmaxx(home_win)-win_text[0].length())/2, "%s", win_text[0].c_str());
    mvwprintw(enemy_win,1,(getmaxx(enemy_win)-win_text[1].length())/2,"%s", win_text[1].c_str());

}

GameUI::~GameUI(){
    endwin();
}

void GameUI::buildup_gameboard(){
    int x =  2* BATTLEFIELD_HEIGHT+1;
    int y = x;
    if(getmaxx(stdscr) / 3 > x)
        x = getmaxx(stdscr) / 3;
    if(getmaxy(stdscr) > y)
        y = getmaxy(stdscr) - 5 ;

    home_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(x,y,home_win);
    enemy_field = std::unique_ptr<BattleFieldUI>(new BattleFieldUI(x,y,enemy_win);
    command_center = std::unique_ptr<CommandCenter>(new CommandCenter
}

BattleFieldUI GameUI::get_home_field(){
    return this->home_field;
}

BattleFieldUI GameUI::get_enemy_field(){
    return this->enemy_field;
}

CommandCenterCombatLog GameUI::get_command_log(){
    return this->cmd_log;
}

CommandCenterStatistics GameUI::get_command_statistics(){
    return this->cmd_statistics;
}

void GameUI::hide_field(BattleField home_content){
    home_field.toggle_field_visibility(COLOR_PAIR(2);
}

void GameUI::draw_field(WINDOW *win, BattleField field){
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

void GameUI::show_field(){
    home_field.toggle_field_visibility(COLOR_PAIR(1));
}

WINDOW* GameUI::get_home_win(){
    return this->home_win;
}

WINDOW* GameUI::get_enemy_win(){
    return this->enemy_win;
}
