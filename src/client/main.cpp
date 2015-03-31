#include "BattleFieldUI.h"
#include "common/BattleField.h"

int main() {
    BattleField field;
    BattleFieldUI test;
    test.draw_home_field(field);
    test.draw_enemy_field(field);
    position_t pos(1,1);
    test.draw_hit_mark(test.get_home_win(),pos,false);
}
