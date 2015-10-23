#include "EnhancedClient.h"
#include "common/BattleField.h"
#include <common/LogConfig.h>

int main(int argc, char *argv[]) {
    LogConfig logConfig(std::string(argv[0]) + ".log");

    EnhancedClient client;
    client.setup();
/*    BattleField field;
    BattleFieldUI test;
    test.draw_home_field(field);
    test.draw_enemy_field(field);
    test.draw_available_ships(field);
    position_t pos(1,1);
    test.draw_hit_mark(test.get_home_win(),pos,false);
    test.hide_field(field);
    test.show_field(field);*/
}
