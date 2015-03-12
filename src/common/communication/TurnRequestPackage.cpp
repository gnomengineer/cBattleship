#include "TurnRequestPackage.h"

TurnRequestPackage::TurnRequestPackage() {
}

TurnRequestPackage::~TurnRequestPackage() {
}

package_nr_t TurnRequestPackage::get_package_nr() {
    return 5;
}


std::vector<unsigned char> TurnRequestPackage::encode_payload() {
    std::vector<unsigned char> encoded;

    return encoded;
}

void TurnRequestPackage::decode_payload(std::vector<unsigned char> command_data) {
    /* retrieve the following members from the vector
     * your_battlefield
     * enemy_battlefield

     */
}

void TurnRequestPackage::set_your_battlefield(BattleField your_battlefield) {
    this->your_battlefield = your_battlefield;
}

BattleField TurnRequestPackage::get_your_battlefield() {
    return your_battlefield;
}
void TurnRequestPackage::set_enemy_battlefield(BattleField enemy_battlefield) {
    this->enemy_battlefield = enemy_battlefield;
}

BattleField TurnRequestPackage::get_enemy_battlefield() {
    return enemy_battlefield;
}

