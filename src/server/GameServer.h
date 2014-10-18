#ifndef _GAMESERVER_H
#define _GAMESERVER_H

#include "BattleShipServer.h"
#include <common/communication/NetworkInterface.h>
#include <map>

enum GameServerState {
    CHECK_FOR_CONNECTIONS,
    STOP
};


class GameServer {
    private:
        GameServerState current_state;
        BattleShipServer server;

    public:
        GameServer();
        virtual ~GameServer();

        void run();

        GameServerState check_for_connections_state();
};


#endif
