#include "NetworkPackageManager.h"

std::map<package_nr_t, std::unique_ptr<::google::protobuf::Message>> NetworkPackageManager::network_packages;
std::map<size_t, package_nr_t> NetworkPackageManager::type_package_nr_map;

NetworkPackageManager::NetworkPackageManager() {
    if(network_packages.size() == 0) {
        add_network_packages<GameConfigurationPackage,
                             PlayerJoinPackage,
                             PlayerJoinAnswerPackage,
                             GameReadyPackage,
                             ShipPlacementPackage,
                             ShipPlacementResponsePackage,
                             TurnRequestPackage,
                             TurnPackage,
                             TurnResponsePackage,
                             EnemyHitPackage,
                             EnemyDisconnectedPackage,
                             GameEndedPackage>();
    }
}

NetworkPackageManager::~NetworkPackageManager() {
}

NetworkPackage NetworkPackageManager::decode_package(std::vector<unsigned char> package_data) {
    if(!NetworkPackageManager::check_packaging(package_data)) throw std::runtime_error("frame is packaged incorrectly");

    // remove terminator & header
    int size = this->get_package_size(package_data);
    package_data.erase(package_data.begin() + (size - 1));
    package_data.erase(package_data.begin(), package_data.begin() + 2);

    std::string package_data_str(package_data.begin(), package_data.end());

    NetworkPackage network_package;
    bool result = network_package.ParseFromString(package_data_str);
    if(!result) throw std::runtime_error("couldn't parse pacakge");

    package_nr_t package_nr = network_package.package_nr();
    if(network_packages.find(package_nr) == network_packages.end()) throw std::runtime_error("invalid package nr");

    return network_package;
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
    if(package_data.size() < 2) return -1;
    unsigned short size = 0;
    size |= package_data[0];
    size |= package_data[1] << 8;
    return size;
}

