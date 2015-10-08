#include "PlayerNetworkPackage.h"

PlayerNetworkPackage::PlayerNetworkPackage(NetworkPackage & command, Player & player)
    : package(package), player(player) {
}

NetworkPackage &PlayerNetworkPackage::get_package() {
    return package;
}

Player &PlayerNetworkPackage::get_player() {
    return player;
}

