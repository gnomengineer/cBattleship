#ifndef _PLAYERNETWORKPACKAGE_H
#define _PLAYERNETWORKPACKAGE_H

#include <common/communication/NetworkPackage.h>
#include "Player.h"

class PlayerNetworkPackage {
    private:
        NetworkPackage & command;
        Player & player;

    public:
        PlayerNetworkPackage(NetworkPackage & command, Player & player);

        Player & get_player();
        NetworkPackage & get_package();
};

#endif // _PLAYERNETWORKPACKAGE_H
