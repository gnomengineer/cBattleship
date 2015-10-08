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
