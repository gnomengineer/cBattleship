#ifndef _PLAYERNETWORKPACKAGE_H
#define _PLAYERNETWORKPACKAGE_H

#include "NetworkPackage.h"
#include <common/Player.h>

class PlayerNetworkPackage {
    private:
        NetworkPackage & command;
        Player & player;

    public:
        PlayerNetworkPackage(NetworkPackage & command, Player & player);

        Player & get_player();
        NetworkPackage & get_network_command();
};

#endif // _PLAYERNETWORKPACKAGE_H
