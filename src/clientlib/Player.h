#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include <memory>

class BattleField;
class GameConfiguration;

class Player {
    private:
        std::string name;
        std::string identity;
        std::unique_ptr<BattleField> battle_field;

    public:
        Player();

        std::string get_name() const;
        void set_name(std::string new_name);
        std::string get_identity() const;
        void set_identity(std::string new_identity);
        void create_battle_field(GameConfiguration &config);
        BattleField &get_battle_field();
};
#endif
