#include "GameConfiguration.h"

#include <packages.pb.h>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

#define MIN_SHIP_LENGTH 1
#define MAX_SHIP_LENGTH 5

GameConfiguration::GameConfiguration()
    : hitspree(false),
      size_y(10),
      size_x(10) {
    ships_available[5] = 1;
    ships_available[4] = 2;
    ships_available[3] = 2;
    ships_available[2] = 3;
}

GameConfiguration::GameConfiguration(boost::program_options::variables_map &vm)
    : hitspree(vm["game.hitspree"].as<bool>()),
      size_y(vm["board.sizey"].as<unsigned int>()), 
      size_x(vm["board.sizex"].as<unsigned int>()) {

    for(unsigned int i = MIN_SHIP_LENGTH; i <= MAX_SHIP_LENGTH; i++) {
        std::string key = "ship." + boost::lexical_cast<std::string>(i) + ".amount";
        ships_available[i] = vm[key].as<unsigned int>();
    }
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

std::map<unsigned int, unsigned int> GameConfiguration::get_ships_available() {
    return ships_available;
}

void GameConfiguration::to_package(GameConfigurationPackage &package) {
    package.set_hitspree(hitspree);
    package.set_size_y(size_y);
    package.set_size_x(size_x);
}
