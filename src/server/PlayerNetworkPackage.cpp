#include "PlayerNetworkPackage.h"

PlayerNetworkPackage::PlayerNetworkPackage(NetworkPackage & command, Player & player)
    : command(command), player(player) {
}

NetworkPackage & PlayerNetworkPackage::get_package() {
    return command;
}

Player & PlayerNetworkPackage::get_player() {
    return player;
}

