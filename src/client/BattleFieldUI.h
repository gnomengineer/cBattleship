#ifndef _BATTLEFIELDUI_H
#define _BATTLEFIELDUI_H

#include <ncurses.h>
#include <vector>
#include "common/BattleField.h"
#include "CursesWindow.h"

class BattleFieldUI : CursesWindow {
    private:
        Player player;
    public: 
        BattleFieldUI(int x, int y, WINDOW *parent_window);
        virtual ~BattleFieldUI();
        void draw_content();
        void draw_hit_mark(bool isShip, position_t position);
        void toggle_field_visibility(int attrs);
        Player &get_player();
};
#endif

