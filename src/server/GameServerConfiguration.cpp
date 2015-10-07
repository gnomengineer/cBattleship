#include "GameServerConfiguration.h"

GameServerConfiguration::GameServerConfiguration()
    : GameConfiguration(),
      bind_address(DEFAULT_BIND_ADDRESS),
      port(DEFAULT_PORT) {
}

GameServerConfiguration::GameServerConfiguration(boost::program_options::variables_map &vm)
    : GameConfiguration(vm),
      bind_address(vm["bind-address"].as<std::string>()), 
      port(vm["port"].as<unsigned short>()) {
}

GameServerConfiguration::~GameServerConfiguration() {
}

std::string GameServerConfiguration::get_bind_address() {
    return bind_address;
}

unsigned short GameServerConfiguration::get_port() {
    return port;
}

