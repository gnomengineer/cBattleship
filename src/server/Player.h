#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include <common/BattleField.h>

class Connection;

class Player {
    private:
        std::unique_ptr<Connection> connection;
        std::string name;
        std::string identity;
        bool is_ready_to_start_;
        BattleField battle_field;

    public:
        Player(Connection *connection, unsigned int size_y, unsigned int size_x);

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
