#ifndef _GAMESERVER_H
#define _GAMESERVER_H

#include "BattleShipServer.h"
#include <common/state-machine/StateMachine.h>
#include <common/communication/NetworkInterface.h>
#include <common/communication/PlayerNetworkCommand.h>
#include <map>
#include <queue>
#include <mutex>

enum GameServerState {
    CHECK_FOR_CONNECTIONS,
    STOP = -1
};


class GameServer {
    private:
        typedef StateMachine<GameServerState, GameServer, PlayerNetworkCommand> StateMachineType;

        StateMachineType state_machine;
        BattleShipServer server;

        std::map<conn_id_t, std::shared_ptr<Player>> players;
        std::queue<PlayerNetworkCommand> input_queue;
        std::mutex queue_lock;

    public:
        GameServer();
        virtual ~GameServer();

        StateMachineType::StateMap get_state_map();
        PlayerNetworkCommand get_input();

        void run();

        GameServerState check_for_connections(PlayerNetworkCommand command);

    private:
        void handle_connection(Connection & conn);
        void handle_player_connection(Connection & conn);
        bool is_new_connection(Connection & conn);
        bool can_handle_new_connection();
        void register_new_connection(Connection & conn);

};


#endif
