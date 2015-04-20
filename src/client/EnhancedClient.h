#ifndef ENHANCEDCLIENT_H
#define ENHANCEDCLIENT_H

#include <clientlib/Player.h>
#include <clientlib/ServerNetworkPackage.h>
#include "BattleFieldUI.h"
#include <string>

class EnhancedClient{

private:
    Player you;
    Player enemy;
    BattleField battle_field;

    std::string direction;
    BattleFieldUI battle_field_ui;

    bool visible_home;
public:
    void run();
    void set_fleet();
    void toggle_home();
private:
    void move_pointer();
};

#endif
