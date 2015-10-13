#include "PlayerNetworkPackage.h"

#include <NetworkPackage.pb.h>
#include "Player.h"

PlayerNetworkPackage::PlayerNetworkPackage(std::shared_ptr<NetworkPackage> package, Player &player)
    : package(package), player(player) {
}

NetworkPackage &PlayerNetworkPackage::get_package() {
    return *package;
}

Player &PlayerNetworkPackage::get_player() {
    return player;
}

