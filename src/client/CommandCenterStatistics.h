#ifndef _COMMANDCENTERSTATISTICS_H
#define _COMMANDCENTERSTATISTICS_H

#include <ncurses.h>
#include <string>

#define STATISTIC_HEIGHT 14
class CommandCenterStatistics : CursesWindow{
    private:
        int shots;
        int hits;
        float calculate_hit_rate();
    public:
        CommandCenterStatistics(int height, int width, int x, int y);
        virtual ~CommandCenterStatistics();
        void increase_shots(bool is_hit);
    private:
        void print_ships(BattleField &battle_field,int attrs_number,int attrs_text);
        void print_keys();
};
#endif
