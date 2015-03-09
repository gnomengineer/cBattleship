#ifndef _PLAYER_H
#define _PLAYER_H

#include <common/BattleField.h>
#include <common/Connection.h>
#include <string>

class Player {
    private:
        Connection & connection;
        std::string name;
        std::string identity;
        bool is_ready_to_start_;
        BattleField battle_field;

    public:
        Player(Connection & connection);

        Connection & get_connection();
        std::string get_name() const;
        void set_name(std::string new_name);
        std::string get_identity() const;
        void set_identity(std::string new_identity);
        bool is_ready_to_start();
        void set_ready_to_start(bool ready_to_start);
        BattleField &get_battle_field();
};
#endif
