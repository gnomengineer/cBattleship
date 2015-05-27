#ifndef ENHANCEDCLIENT_H
#define ENHANCEDCLIENT_H

#include <clientlib/Player.h>
#include <clientlib/ServerNetworkPackage.h>
#include "BattleFieldUI.h"

class EnhancedClient{

private:
    Player you;
    Player enemy;
    BattleField home_field;
    BattleField enemy_field;

    BattleFieldUI battle_field_ui;

    bool visible_home;
public:
    EnhancedClient();
    virtual ~EnhancedClient();
    void run();
private:
    void set_fleet();
    void toggle_home();
    void move_cursor(WINDOW *win, int direction, int x, int y);
    void draw_game_ui();
};

#endif
