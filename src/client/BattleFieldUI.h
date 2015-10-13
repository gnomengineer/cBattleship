#ifndef _BATTLEFIELDUI_H
#define _BATTLEFIELDUI_H

#include <ncurses.h>
#include <vector>
#include <clientlib/Player.h>
#include "CursesWindow.h"
#include <common/position.h>

class BattleFieldUI : public CursesWindow {
    private:
        Player player;
    public: 
        BattleFieldUI(int x, int y, WINDOW *parent_window);
        virtual ~BattleFieldUI();
        void draw_content();
        void draw_hit_mark(bool isShip, position_t position);
        void toggle_field_visibility(bool visible_flag);
        Player &get_player();
        BattleField &get_players_battle_field();
        position_t get_position();
};
#endif

