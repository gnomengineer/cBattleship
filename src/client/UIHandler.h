#ifndef _UIHANDLER_H
#define _UIHANDLER_H

#include "BattleFieldUI.h"
#include "WinScreenUI.h"

class UIHandler{
    private:
BattleFieldUI battle_field;
WinScreenUI win_screen;
    public:
void refresh_battle_field();
void open_win_screen();
void set_fleet();
void redraw_field();
}

#endif
