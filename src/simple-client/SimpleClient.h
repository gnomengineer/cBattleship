#ifndef _SIMPLECLIENT_H
#define _SIMPLECLIENT_H

#include <common/state-machine/StateMachine.h>
#include <common/communication/NetworkPackageManager.h>
#include <map>
#include <queue>
#include <mutex>
#include <common/Connection.h>
#include "Player.h"
#include "ServerNetworkPackage.h"

enum SimpleClientState {
    GET_IDENTITY,
    WAIT_FOR_GAME_START,
    STOP = -1
};


class SimpleClient {
    private:
        typedef StateMachine<SimpleClientState, SimpleClient, ServerNetworkPackage> StateMachineType;

        StateMachineType state_machine;
        Connection &connection;

        Player you;
        Player enemy;
        std::list<Player*> players_playing;

        std::queue<ServerNetworkPackage> input_queue;
        std::mutex queue_lock;

    public:
        SimpleClient(Connection &connection);
        virtual ~SimpleClient();

        StateMachineType::StateMap get_state_map();
        ServerNetworkPackage get_input();

        void run();

        SimpleClientState get_identity(ServerNetworkPackage server_package);
        SimpleClientState wait_for_game_start(ServerNetworkPackage server_package);

    private:
        std::string ask_user(std::string prompt, std::string default_value);

        void ask_ship_placement();
        unsigned int ask_ship_length();
        orientation_t ask_ship_orientation();
        position_t ask_ship_position(unsigned int length, orientation_t orientation);
        position_coordinate_t ask_ship_coord(std::string coord_name);
        void print_ships_available();

        std::string get_ship_name_by_length(unsigned int length);
        void print_your_battlefield();
};


#endif
