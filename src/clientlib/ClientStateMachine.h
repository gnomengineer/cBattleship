#ifndef CLIENTSTATEMACHINE_H
#define CLIENTSTATEMACHINE_H

#include <common/state-machine/StateMachine.h>
#include <common/NetworkPackageManager.h>
#include <map>
#include <queue>
#include <mutex>
#include <common/Connection.h>
#include <boost/asio.hpp>
#include "Player.h"
#include "GameEvents.h"

enum ClientState {
    GET_IDENTITY,
    WAIT_FOR_GAME_START,
    YOUR_TURN,
    STOP = -1
};

class ClientStateMachine {
    private:
        typedef StateMachine<ClientState, ClientStateMachine, NetworkPackage&> StateMachineType;
        StateMachineType state_machine;

        std::unique_ptr<Connection> connection;

        Player you;
        Player enemy;
        std::list<Player*> players_playing;

        std::queue<NetworkPackage> input_queue;
        std::mutex queue_lock;

        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver;
        boost::asio::ip::tcp::resolver::query query;
        std::unique_ptr<boost::asio::ip::tcp::socket> socket;

        position_t last_turn_position;

    public:
        GameEvents events;

        ClientStateMachine(std::string connection_string);
        ~ClientStateMachine();

        StateMachineType::StateMap get_state_map();
        NetworkPackage& get_input();

        ClientState get_identity(NetworkPackage &package);
        ClientState wait_for_game_start(NetworkPackage &package);
        ClientState your_turn(NetworkPackage &package);

        void run();
        void stop();

        void get_turn();
};

#endif /* CLIENTSTATEMACHINE_H */
