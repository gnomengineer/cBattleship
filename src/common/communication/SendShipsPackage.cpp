#include "SendShipsPackage.h"
#include <algorithm>

SendShipsPackage::SendShipsPackage() {
}

SendShipsPackage::~SendShipsPackage() {
}

package_nr_t SendShipsPackage::get_package_nr() {
    return 7;
}


std::vector<unsigned char> SendShipsPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    std::for_each(ships.begin(), ships.end(), [&](std::pair<int, orientation_t> p) {
        encoded.push_back(p.first & 0xFF);
        encoded.push_back(p.second & 0x1);
    });
    return encoded;
}

void SendShipsPackage::decode_payload(std::vector<unsigned char> command_data) {
    int num_ships = command_data.size() / 2;
    std::vector<std::pair<int, orientation_t>> ships_received;
    for(int i = 0; i < num_ships; i++) {
        int ship_length = command_data[i * 2];
        orientation_t orientation = static_cast<orientation_t>(command_data[i * 2 + 1]);
        std::pair<int, orientation_t> ship = std::make_pair(ship_length, orientation);
        ships_received.push_back(ship);
    }
}

void SendShipsPackage::set_ships(std::vector<std::pair<unsigned int, orientation_t>> ships) {
    this->ships = ships;
}

std::vector<std::pair<unsigned int, orientation_t>> SendShipsPackage::get_ships() {
    return ships;
}

