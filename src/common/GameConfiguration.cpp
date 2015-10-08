#include "GameConfiguration.h"

GameConfiguration::GameConfiguration()
    : hitspree(false) {
}

GameConfiguration::GameConfiguration(boost::program_options::variables_map &vm)
    : hitspree(vm["game.hitspree"].as<bool>()) {
}

GameConfiguration::GameConfiguration(GameConfigurationPackage &game_configuration_package)
    : hitspree(game_configuration_package.hitspree()) {
}

GameConfiguration::~GameConfiguration() {
}

bool GameConfiguration::get_hitspree() {
    return hitspree;
}

void GameConfiguration::to_package(GameConfigurationPackage &package) {
    package.set_hitspree(hitspree);
}
