#ifndef _PLAYERNETWORKCOMMAND_H
#define _PLAYERNETWORKCOMMAND_H

#include "NetworkCommand.h"
#include <common/Player.h>

class PlayerNetworkCommand {
    private:
        NetworkCommand & command;
        Player & player;

    public:
        PlayerNetworkCommand(NetworkCommand & command, Player & player);

        Player & get_player();
        NetworkCommand & get_network_command();
};

#endif // _PLAYERNETWORKCOMMAND_H
