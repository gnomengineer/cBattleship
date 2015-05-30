#ifndef _COMMANDCENTER_H
#define _COMMANDCENTER_H

#include <ncurses.h>
#include <string>

#define STATISTIC_HEIGHT 7
class CommandCenter : CursesWindow{
    private:
        int shots;
        int hits;
        float calculate_hit_rate();
    public:
        CommandCenter(int height, int width, int x, int y);
        virtual ~CommandCenter();
        void increase_shots(bool is_hit);
        void print_ships(BattleField &battle_field,int attrs_number,int attrs_text);
};
#endif
