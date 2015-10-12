#include "GameConfiguration.h"

GameConfiguration::GameConfiguration()
    : hitspree(false),
      size_y(10),
      size_x(10) {
}

GameConfiguration::GameConfiguration(boost::program_options::variables_map &vm)
    : hitspree(vm["game.hitspree"].as<bool>()),
      size_y(vm["board.sizey"].as<unsigned int>()), 
      size_x(vm["board.sizex"].as<unsigned int>()) {
}

GameConfiguration::GameConfiguration(GameConfigurationPackage &game_configuration_package)
    : hitspree(game_configuration_package.hitspree()),
      size_y(game_configuration_package.size_y()), 
      size_x(game_configuration_package.size_x()) {
}

GameConfiguration::~GameConfiguration() {
}

bool GameConfiguration::get_hitspree() {
    return hitspree;
}

unsigned int GameConfiguration::get_size_y() {
    return size_y;
}

unsigned int GameConfiguration::get_size_x() {
    return size_x;
}

void GameConfiguration::to_package(GameConfigurationPackage &package) {
    package.set_hitspree(hitspree);
    package.set_size_y(size_y);
    package.set_size_x(size_x);
}
