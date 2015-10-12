#ifndef _PLAYER_H
#define _PLAYER_H

#include <common/BattleField.h>
#include <string>
#include <memory>

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
        void create_battle_field(unsigned int battlefield_size_y, unsigned int battlefield_size_x);
        BattleField &get_battle_field();
};
#endif
