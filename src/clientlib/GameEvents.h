#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include <boost/signals2/signal.hpp>

namespace signals = boost::signals2;

/**
 * A collection of signals a potential client can .connect() to
 */
class GameEvents {
    public:
        //========== Connection Signals ==============================
        /**
         * This event is raised when you just started to try to connect
         * to the server.
         *
         * @param std::string connection_string the connection string
         *                                      used to connect.
         */
        signals::signal<void (std::string connection_string)> connecting;

        /**
         * This event is raised when the connection to the server
         * was established.
         */
        signals::signal<void ()> connected;
        //========== /Connection Signals =============================


        //========== Authentication Signals ==========================
        /**
         * This event is raised when the server sends you it's game
         * configuration.
         * @param GameConfiguration config  the configuration used by
         *                                  the server.
         */
        signals::signal<void (GameConfiguration config)> get_game_configuration;

        /**
         * This event is raised when the server requests your
         * player name.
         *
         * @param std::string name      A reference to a string to save
         *                              your name in.
         */
        signals::signal<void (std::string &name)> get_player_name;

        /**
         * This event is raised after you've sent your name to
         * the server. The server then generates an authentication
         * string (called "identity") and sends it to the client.
         *
         * @param std::string identity  Your authentication string for
         *                              further requests to the server.
         */
        signals::signal<void (std::string identity)> new_identity;
        //========== /Authentication Signals =========================


        //========== Ship Placement Signals ==========================
        /**
         * This event is raised when you are supposed to place your
         * ships.
         *
         * @param Player& you           your Player object. Place the ships
         *                              onto the Battlefield of the Player
         *                              object.
         */
        signals::signal<void (Player &you)> place_ships;

        /**
         * This event is raised when you need to wait for the
         * confirmation of the server if your ship placement is valid.
         */
        signals::signal<void ()> place_ship_confirmation_wait;

        /**
         * This event is raised when everything is ok with your
         * ship placement.
         */
        signals::signal<void ()> place_ship_ok;

        /**
         * This event is raised when there is an error with your ship placment.
         *
         * @param bool out_of_bounds    true if one of your ships was out of
         *                              bounds of the battlefield
         * @param bool overlap          true if some of your ship overlap
         * @param int remaining_ships   the number of remaining_ships you need
         *                              to place.
         */
        signals::signal<void (bool out_of_bounds, bool overlap, int remaining_ships)> place_ship_error;
        //========== /Ship Placement Signals =========================


        //========== Turn Handling Signals ===========================
        /**
         * This event is raised when a new turn is expected from you.
         *
         * @param Player& you           your Player object
         * @param Player& enemy         the enemy's Player object
         * @param position_t& position  Reference to a position_t object
         *                              to fill your turn in.
         */
        signals::signal<void (Player &you, Player &enemy, position_t &position)> get_turn;

        /**
         * This event is raised after you've sent your turn to the
         * server for validation. It tells you the server is validating
         * your turn.
         */
        signals::signal<void ()> turn_confirmation_wait;

        /**
         * This event is raised after you've sent your turn to the
         * server for validation. It informs you about your turn.
         *
         * @param bool did_you_hit
         * @param int ship_of_length_destroyed  if 0, no ship has been destroyed,
         *                                      if != 0, a ship of this length has
         *                                      been destroyed by the last urn
         */
        signals::signal<void (bool did_you_hit, int ship_of_length_destroyed)> turn_ok;

        /**
         * This event is raised if your turn was invalid
         * E.g. position out of range etc.
         */
        signals::signal<void ()> turn_error;

        /**
         * This event is raised if the enemy has hit your Battlefield
         *
         * @param bool hit              wheter the enemy hit a ship
         * @param position_t position   the position on your Battlefield
         *                              where the enemy hit
         */
        signals::signal<void (bool hit, position_t position)> enemy_hit;

        /**
         * This event is raised if you need to wait for the
         * enemy to make a turn.
         */
        signals::signal<void ()> enemy_wait;
        //========== /Turn Handling Signals ==========================


        //========== Game Ending Signals =============================
        /**
         * This event is raised when the enemy suddenly disconnects
         * from the game. All game data can be discarded as it is useless
         * as of now.
         */
        signals::signal<void ()> enemy_disconnected;

        /**
         * Event raised when the game ended. This happens when
         * one side has sunken all the enemy ships.
         *
         * @param bool won      true if you won, false if you didn't
         * @param Player& you   your Player object
         * @param Player& enemy the enemys Player object
         */
        signals::signal<void (bool won, Player &you, Player &enemy)> game_ended;
        //========== /Game Ending Signals ============================

};

#endif /* GAMEEVENTS_H */
