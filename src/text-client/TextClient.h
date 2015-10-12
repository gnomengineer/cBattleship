#ifndef _TEXTCLIENT_H
#define _TEXTCLIENT_H


#include <clientlib/ClientStateMachine.h>


class TextClient {
    private:
        position_t last_turn_position;
        ClientStateMachine client_state_machine;

    public:
        TextClient(std::string connection_string);
        virtual ~TextClient();

        void run();

    private:
        std::string ask_user(std::string prompt, std::string default_value);

        void ask_ship_placement(Player &you);
        unsigned int ask_ship_length(Player &you);
        orientation_t ask_ship_orientation();
        position_t ask_position(Player &you);
        position_coordinate_t ask_coord(std::string coord_name);
        position_t ask_turn(Player &you, Player &enemy);
        void print_ships_available(BattleField &battle_field);

        std::string get_ship_name_by_length(unsigned int length);
        void print_battle_field(Player &player);
};


#endif
