#ifndef _PLAYER_H
#define _PLAYER_H

#include <common/BattleField.h>
#include <string>

class Player {
    private:
        std::string name;
        std::string identity;
        BattleField battle_field;

    public:
        Player();

        std::string get_name() const;
        void set_name(std::string new_name);
        std::string get_identity() const;
        void set_identity(std::string new_identity);
        BattleField &get_battle_field();
};
#endif
