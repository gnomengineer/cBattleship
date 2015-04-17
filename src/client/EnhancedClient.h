#ifndef ENHANCEDCLIENT_H
#define ENHANCEDCLIENT_H

#include <clientlib/Player.h>
#include <clientlib/ServerNetworkPackage.h>
#include "BattleFieldUI.h"

class EnhancedClient{

private:
    Player you;
    Player enemy;
    BattleField battle_field;

    BattleFieldUI battle_field_ui;
    bool visible_home;
public:
    void run();
    void set_fleet();
    void toggle_home();
};

#endif
