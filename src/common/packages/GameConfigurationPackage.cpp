#include "GameConfigurationPackage.h"

GameConfigurationPackage::GameConfigurationPackage() : config() {
}

GameConfigurationPackage::~GameConfigurationPackage() {
}

package_nr_t GameConfigurationPackage::get_package_nr() {
    return 11;
}


std::vector<unsigned char> GameConfigurationPackage::encode_payload() {
    return config.to_bytes();
}

void GameConfigurationPackage::decode_payload(std::vector<unsigned char> package_data) {
    config.from_bytes(package_data, 0);
}

void GameConfigurationPackage::set_config(GameConfiguration config) {
    this->config = config;
}

GameConfiguration GameConfigurationPackage::get_config() {
    return config;
}
