#ifndef _GAMESERVER_H
#define _GAMESERVER_H

#include "BattleShipServer.h"
#include <common/state-machine/StateMachine.h>
#include <common/communication/NetworkPackageManager.h>
#include "PlayerNetworkPackage.h"
#include <map>
#include <queue>
#include <mutex>

enum GameServerState {
    CHECK_FOR_CONNECTIONS,
    SETUP_GAME,
    STOP = -1
};


class GameServer {
    private:
        typedef StateMachine<GameServerState, GameServer, PlayerNetworkPackage> StateMachineType;

        StateMachineType state_machine;
        BattleShipServer server;


        std::list<Player*> players_playing;
        std::map<conn_id_t, std::unique_ptr<Player>> players;
        std::queue<PlayerNetworkPackage> input_queue;
        std::mutex queue_lock;

    public:
        GameServer();
        virtual ~GameServer();

        StateMachineType::StateMap get_state_map();
        PlayerNetworkPackage get_input();

        void run();

        GameServerState check_for_connections(PlayerNetworkPackage player_package);
        GameServerState setup_game(PlayerNetworkPackage player_package);

    private:
        void handle_connection(Connection & conn);
        void handle_player_connection(Connection & conn);
        bool is_new_connection(Connection & conn);
        bool can_handle_new_connection();
        void register_new_connection(Connection & conn);

};


#endif
