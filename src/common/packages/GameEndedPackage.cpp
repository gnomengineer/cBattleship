#include "GameEndedPackage.h"
#include "ShipDataUtil.h"

GameEndedPackage::GameEndedPackage() {
}

GameEndedPackage::~GameEndedPackage() {
}

package_nr_t GameEndedPackage::get_package_nr() {
    return 10;
}


std::vector<unsigned char> GameEndedPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    NetworkPackage::add_to_bytes(encoded, won);
    ShipDataUtil::add_ships_to_bytes(encoded, enemy_ships); 
    return encoded;
}

void GameEndedPackage::decode_payload(std::vector<unsigned char> package_data) {
    NetworkPackage::get_from_bytes(package_data, 0, won);
    enemy_ships = ShipDataUtil::get_ships_from_bytes(package_data, sizeof(won)); 
}

void GameEndedPackage::set_won(bool won) {
    this->won = won;
}

bool GameEndedPackage::get_won() {
    return won;
}
void GameEndedPackage::set_enemy_ships(std::vector<ShipData> enemy_ships) {
    this->enemy_ships = enemy_ships;
}

std::vector<ShipData> GameEndedPackage::get_enemy_ships() {
    return enemy_ships;
}
