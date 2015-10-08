#ifndef _PLAYERNETWORKPACKAGE_H
#define _PLAYERNETWORKPACKAGE_H

#include "Player.h"
#include <packages.pb.h>

class PlayerNetworkPackage {
    private:
        NetworkPackage &package;
        Player &player;

    public:
        PlayerNetworkPackage(NetworkPackage &command, Player &player);

        Player &get_player();
        NetworkPackage &get_package();
};

#endif // _PLAYERNETWORKPACKAGE_H
