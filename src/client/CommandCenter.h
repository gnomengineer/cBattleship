#ifndef _COMMANDCENTER_H
#define _COMMANDCENTER_H

#include <ncurses.h>
#include <string>

#define STATISTIC_HEIGHT 7
class CommandCenter{
    private:
        WINDOW *game_progress_window;
        WINDOW *game_statistics_window;
        int shots;
        int hits;
        float calculate_hit_rate();
    public:
        CommandCenter(int height, int width);
        virtual ~CommandCenter();
        void write_message(std::string message);
        void increase_shots(bool is_hit);
        void print_ships(BattleField &battle_field,int attrs_number,int attrs_text);
};
#endif
