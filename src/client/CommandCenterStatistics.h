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
        std::map<unsigned int, unsigned int> ship_list;
    public:
        CommandCenterStatistics(int height, int width, int x, int y);
        virtual ~CommandCenterStatistics();
        void increase_shots(bool is_hit);
        int print_ships();
        void print_keys();
        void set_ship_list(std::map<unsigned int, unsigned int> new_list);
};
#endif
