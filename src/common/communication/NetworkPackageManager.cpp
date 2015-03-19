#include "NetworkPackageManager.h"

#define PACKAGE_TERMINATOR 0xCD

std::map<package_nr_t, std::unique_ptr<NetworkPackage>> NetworkPackageManager::network_commands;

NetworkPackageManager::NetworkPackageManager() {
    if(network_commands.size() == 0) {
        add_network_commands<PlayerJoinPackage,
                             PlayerJoinAnswerPackage,
                             GameReadyPackage,
                             ShipPlacementPackage,
                             TurnRequestPackage,
                             TurnPackage>();
    }
}

std::vector<unsigned char> NetworkPackageManager::encode_command(NetworkPackage& command) {
    std::vector<unsigned char> encoded(3);
    encoded[0] = command.get_package_nr();

    auto payload = command.encode_payload();
    encoded.insert(encoded.end(), payload.begin(), payload.end());
    encoded.push_back(PACKAGE_TERMINATOR);

    unsigned short size = encoded.size();
    encoded[1] = size & 0xFF;
    encoded[2] = (size >> 8) & 0xFF;

    return encoded;
}

NetworkPackage& NetworkPackageManager::decode_command(std::vector<unsigned char> command_data) {
    if(!NetworkPackageManager::check_packaging(command_data)) throw std::runtime_error("frame is packaged incorrectly");
    package_nr_t package_nr = command_data[0];
    int size = this->get_package_size(command_data);

    if(network_commands.find(package_nr) == network_commands.end()) throw std::runtime_error("invalid command nr");

    // remove terminator & header
    command_data.erase(command_data.begin() + (size - 1));
    command_data.erase(command_data.begin(), command_data.begin() + 3);

    auto& command = *network_commands[package_nr];
    command.decode_payload(command_data);

    return command;
}

bool NetworkPackageManager::check_packaging(std::vector<unsigned char> command_data) {
    int size = this->get_package_size(command_data);
    if(size == -1) return false;
    if(size < 4) return false;
    if(command_data.size() < size) return false;
    if(command_data[size - 1] != PACKAGE_TERMINATOR) return false;
    return true;
}

int NetworkPackageManager::get_package_size(std::vector<unsigned char> command_data) {
    if(command_data.size() < 3) return -1;
    unsigned short size = 0;
    size |= command_data[1];
    size |= command_data[2] << 8;
    return size;
}
