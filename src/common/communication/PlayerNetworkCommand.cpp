#include "PlayerNetworkCommand.h"

PlayerNetworkCommand::PlayerNetworkCommand(NetworkCommand & command, Player & player)
    : command(command), player(player) {
}

NetworkCommand & PlayerNetworkCommand::get_network_command() {
    return command;
}

Player & PlayerNetworkCommand::get_player() {
    return player;
}

