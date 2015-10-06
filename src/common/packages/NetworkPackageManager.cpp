#include "NetworkPackageManager.h"

std::map<package_nr_t, std::unique_ptr<NetworkPackage>> NetworkPackageManager::network_commands;

NetworkPackageManager::NetworkPackageManager() {
    if(network_commands.size() == 0) {
        add_network_commands<PlayerJoinPackage,
                             PlayerJoinAnswerPackage,
                             GameReadyPackage,
                             ShipPlacementPackage,
                             ShipPlacementResponsePackage,
                             TurnRequestPackage,
                             TurnPackage,
                             TurnResponsePackage,
                             EnemyDisconnectedPackage,
                             GameEndedPackage>();
    }
}

NetworkPackage& NetworkPackageManager::decode_package(std::vector<unsigned char> package_data) {
    if(!NetworkPackageManager::check_packaging(package_data)) throw std::runtime_error("frame is packaged incorrectly");
    package_nr_t package_nr = package_data[0];
    int size = this->get_package_size(package_data);

    if(network_commands.find(package_nr) == network_commands.end()) throw std::runtime_error("invalid command nr");

    // remove terminator & header
    package_data.erase(package_data.begin() + (size - 1));
    package_data.erase(package_data.begin(), package_data.begin() + 3);

    auto& package = *network_commands[package_nr];
    std::istringstream archive_stream(std::string(package_data.begin(), package_data.end()));
    boost::archive::polymorphic_text_iarchive archive(archive_stream);
    archive >> package;

    return package;
}

bool NetworkPackageManager::check_packaging(std::vector<unsigned char> package_data) {
    int size = this->get_package_size(package_data);
    if(size == -1) return false;
    if(size < 4) return false;
    if(package_data.size() < size) return false;
    if(package_data[size - 1] != PACKAGE_TERMINATOR) return false;
    return true;
}

int NetworkPackageManager::get_package_size(std::vector<unsigned char> package_data) {
    if(package_data.size() < 3) return -1;
    unsigned short size = 0;
    size |= package_data[1];
    size |= package_data[2] << 8;
    return size;
}
