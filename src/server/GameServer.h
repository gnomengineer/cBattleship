#ifndef _GAMESERVER_H
#define _GAMESERVER_H

#include "ConnectionServer.h"
#include <common/state-machine/StateMachine.h>
#include <common/packages/NetworkPackageManager.h>
#include "PlayerNetworkPackage.h"
#include <map>
#include <queue>
#include <mutex>

enum GameServerState {
    CHECK_FOR_CONNECTIONS,
    SETUP_GAME,
    TURN_WAIT,
    STOP = -1
};


class GameServer {
    private:
        typedef StateMachine<GameServerState, GameServer, PlayerNetworkPackage> StateMachineType;

        StateMachineType state_machine;
        ConnectionServer server;


        std::list<Player*> players_playing;
        std::list<Player*>::iterator current_player;
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
        GameServerState turn_wait(PlayerNetworkPackage player_package);

    private:
        void handle_connection(Connection & conn);
        void handle_player_connection(Connection & conn);
        bool is_authenticated(NetworkPackage & command, Player & player);
        bool is_new_connection(Connection & conn);
        bool can_handle_new_connection();
        void register_new_connection(Connection & conn);
        void next_player();
        Player& get_enemy();
        void request_turn(bool enemy_hit, position_t position);

};


#endif
