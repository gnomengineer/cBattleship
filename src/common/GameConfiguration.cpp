#include "GameConfiguration.h"

GameConfiguration::GameConfiguration()
    : hitspree(false) {
}

GameConfiguration::GameConfiguration(boost::program_options::variables_map &vm)
    : hitspree(vm["game.hitspree"].as<bool>()) {
}

GameConfiguration::~GameConfiguration() {
}

bool GameConfiguration::get_hitspree() {
    return hitspree;
}

std::vector<unsigned char> GameConfiguration::to_bytes() {
    std::vector<unsigned char> result;
    NetworkPackage::add_to_bytes(result, hitspree);
    return result;
}
void GameConfiguration::from_bytes(std::vector<unsigned char> &bytes, unsigned int index) {
    NetworkPackage::get_from_bytes(bytes, index, hitspree);
}
