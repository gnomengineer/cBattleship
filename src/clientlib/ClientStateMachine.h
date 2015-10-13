#ifndef CLIENTSTATEMACHINE_H
#define CLIENTSTATEMACHINE_H

#include <boost/asio.hpp>
#include <map>
#include <mutex>
#include <common/state-machine/StateMachine.h>
#include <NetworkPackage.pb.h>
#include "GameEvents.h"
#include "Player.h"

class Connection;
class GameConfiguration;

enum ClientState {
    INITIALIZE,
    WAIT_FOR_JOIN,
    WAIT_FOR_GAME_START,
    YOUR_TURN,
    STOP = -1
};

class ClientStateMachine {
    private:
        typedef StateMachine<ClientState, ClientStateMachine, NetworkPackage&> StateMachineType;
        StateMachineType state_machine;

        std::unique_ptr<Connection> connection;

        std::unique_ptr<GameConfiguration> config;

        Player you;
        Player enemy;

        std::list<Player*> players_playing;

        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver;
        boost::asio::ip::tcp::resolver::query query;
        std::unique_ptr<boost::asio::ip::tcp::socket> socket;

        position_t last_turn_position;

    public:
        GameEvents events;

        ClientStateMachine(std::string host, unsigned int port);
        ~ClientStateMachine();

        StateMachineType::StateMap get_state_map();
        NetworkPackage &get_input();

        ClientState initialize(NetworkPackage &package);
        ClientState wait_for_join(NetworkPackage &package);
        ClientState wait_for_game_start(NetworkPackage &package);
        ClientState your_turn(NetworkPackage &package);

        void run();
        void stop();

        void get_turn();
        void ask_for_ship_placement();
};

#endif /* CLIENTSTATEMACHINE_H */
