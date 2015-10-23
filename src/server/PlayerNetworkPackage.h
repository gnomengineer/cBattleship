#ifndef _PLAYERNETWORKPACKAGE_H
#define _PLAYERNETWORKPACKAGE_H

#include <memory>

class Player;
class NetworkPackage;

class PlayerNetworkPackage {
    private:
        std::shared_ptr<NetworkPackage> package;
        Player &player;

    public:
        PlayerNetworkPackage(std::shared_ptr<NetworkPackage> package, Player &player);

        Player &get_player();
        NetworkPackage &get_package();
};

#endif // _PLAYERNETWORKPACKAGE_H
