#ifndef _COMMANDCENTERSTATISTICS_H
#define _COMMANDCENTERSTATISTICS_H

#include <ncurses.h>
#include "CursesWindow.h"
#include "common/BattleField.h"
#include <string>

class CommandCenterStatistics : public CursesWindow{
    private:
        float shots;
        float hits;
        float calculate_hit_rate();
    public:
        CommandCenterStatistics(int height, int width, int x, int y);
        virtual ~CommandCenterStatistics();
        void increase_shots(bool is_hit);
        void print_ships(BattleField &battle_field);
        void print_keys();
};
#endif
