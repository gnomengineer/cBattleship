#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include <boost/signals2/signal.hpp>

namespace signals = boost::signals2;

class GameEvents {
    public:
        signals::signal<void (std::string connection_string)> connecting;
        signals::signal<void ()> connected;

        signals::signal<void (bool hitspree)> get_server_configuration;

        signals::signal<void (std::string &name)> get_player_name;
        signals::signal<void (std::string)> new_identity;

        signals::signal<void (Player &you)> place_ships;
        signals::signal<void ()> place_ship_confirmation_wait;
        signals::signal<void ()> place_ship_ok;
        signals::signal<void (bool out_of_bounds, bool overlap, int remaining_ships)> place_ship_error;

        signals::signal<void (Player &you, Player &enemy, position_t &position)> get_turn;
        signals::signal<void ()> turn_confirmation_wait;
        /* ship_of_length_destroyed == 0, if no ship has been destroyed */
        signals::signal<void (bool did_you_hit, int ship_of_length_destroyed)> turn_ok;
        signals::signal<void ()> turn_error;

        signals::signal<void (Player &you, position_t position)> enemy_hit;
        signals::signal<void ()> enemy_wait;
        signals::signal<void ()> enemy_disconnected;

        signals::signal<void (bool won, Player &you, Player &enemy)> game_ended;

};

#endif /* GAMEEVENTS_H */
