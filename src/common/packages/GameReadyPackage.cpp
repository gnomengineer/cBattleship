#include "GameReadyPackage.h"
#include <common/BattleField.h>

GameReadyPackage::GameReadyPackage() {
}

GameReadyPackage::~GameReadyPackage() {
}

package_nr_t GameReadyPackage::get_package_nr() {
    return 3;
}


std::vector<unsigned char> GameReadyPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    if(enemy_name.size() >= PLAYER_NAME_MAX_LENGTH) {
        encoded.insert(encoded.end(), enemy_name.begin(), enemy_name.begin() + PLAYER_NAME_MAX_LENGTH);
    } else {
        encoded.insert(encoded.end(), enemy_name.begin(), enemy_name.end());
    }
    return encoded;
}

void GameReadyPackage::decode_payload(std::vector<unsigned char> package_data) {
    if(package_data.size() >= PLAYER_NAME_MAX_LENGTH) {
        enemy_name = std::string(package_data.begin(), package_data.begin() + PLAYER_NAME_MAX_LENGTH);
    } else {
        enemy_name = std::string(package_data.begin(), package_data.end());
    }
}

void GameReadyPackage::set_enemy_name(std::string enemy_name) {
    this->enemy_name = enemy_name;
}

std::string GameReadyPackage::get_enemy_name() {
    return enemy_name;
}
