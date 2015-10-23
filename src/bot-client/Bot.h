#ifndef _BOT_H
#define _BOT_H

#include <string>
#include <vector>
#include <ShipData.pb.h>
#include <common/position.h>

class GameConfiguration;
class BattleField;
class Process;
class Player;

class Bot {
    private:
        std::string executable;
    public:
        Bot(std::string bot_executable);
        ~Bot();

        std::string get_bot_name();
        std::vector<ShipData> make_ship_placement(GameConfiguration &config);
        position_t make_turn(Player &you, Player &enemy, GameConfiguration &config);

    private:
        Process *make_process(std::string call_type);
        void send_rules(Process &process, GameConfiguration &config);
        void send_battle_field_size(Process &process, GameConfiguration &config);
        void send_ships_available(Process &process, GameConfiguration &config);
        void send_own_battle_field(Process &process, BattleField &your_battle_field);
        void send_enemy_battle_field(Process &process, BattleField &enemy_battle_field);
        void send_battle_field(Process &process, BattleField &battlefield, std::string type);
        void send_hit_messages(Process &process, bool hit);
};
#endif /* _BOT_H */
