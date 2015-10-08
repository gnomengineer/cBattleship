#ifndef _PLAYERNETWORKPACKAGE_H
#define _PLAYERNETWORKPACKAGE_H

#include "Player.h"
#include <google/protobuf/message.h>

class PlayerNetworkPackage {
    private:
        ::google::protobuf::Message &package;
        Player &player;

    public:
        PlayerNetworkPackage(::google::protobuf::Message &command, Player &player);

        Player &get_player();
        NetworkPackage &get_package();
};

#endif // _PLAYERNETWORKPACKAGE_H
