#ifndef _BATTLEFIELDUI_H
#define _BATTLEFIELDUI_H

#include <ncurses.h>
#include <vector>

class BattleFieldUI {
    private:
        WINDOW *field_window;
        BattleField *field_info;
    public: 
        BattleFieldUI();
        virtual ~BattleFieldUI();
        void move_cursor(int x, int y);
        void draw_content();
        void draw_hit_mark(bool isShip, position_t position);
        void toggle_field_visibility(int attrs);
        WINDOW *get_window();
        BattleField *get_battle_field;
};
#endif
