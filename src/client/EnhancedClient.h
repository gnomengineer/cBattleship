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

    std::string direction;
    BattleFieldUI battle_field_ui;

    bool visible_home;
public:
    EnhancedClient();
    virtual ~EnhancedClient();
    void run();
    void set_fleet();
    void toggle_home();
private:
    void move_curser();
};

#endif
