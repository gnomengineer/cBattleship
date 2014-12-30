#include "PlayerNetworkPackage.h"

PlayerNetworkPackage::PlayerNetworkPackage(NetworkPackage & command, Player & player)
    : command(command), player(player) {
}

NetworkPackage & PlayerNetworkPackage::get_network_command() {
    return command;
}

Player & PlayerNetworkPackage::get_player() {
    return player;
}

