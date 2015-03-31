#include "ShipPlacementPackage.h"

ShipPlacementPackage::ShipPlacementPackage() {
}

ShipPlacementPackage::~ShipPlacementPackage() {
}

package_nr_t ShipPlacementPackage::get_package_nr() {
    return 4;
}


std::vector<unsigned char> ShipPlacementPackage::encode_payload() {
    std::vector<unsigned char> encoded = AuthenticatedNetworkPackage::encode_payload();
    for(auto it = ship_data.begin(); it != ship_data.end(); it++) {
        auto &ship = *it;
        encoded.push_back(ship.length & 0xFF);
        encoded.push_back(ship.orientation & 0x1);
        encoded.push_back(ship.start_position.y & 0xFF);
        encoded.push_back(ship.start_position.x & 0xFF);
    }
    return encoded;
}

void ShipPlacementPackage::decode_payload(std::vector<unsigned char> command_data) {
    AuthenticatedNetworkPackage::decode_payload(command_data);
    const int ship_length = 4;
    const int ships_length = command_data.size() - IDENTITY_LENGTH;
    const int num_ships = ship_length / ship_length;
    ship_data.clear();
    for(int i = 0; i < num_ships; i++) {
        const int ship_offset = IDENTITY_LENGTH + i * ship_length;
        ShipData data = { command_data[ship_offset],
                          static_cast<orientation_t>(command_data[ship_offset + 1] & 1),
                          { command_data[ship_offset + 2],
                            command_data[ship_offset + 3],
                          },
                        };
        ship_data.push_back(data);
    }
}

void ShipPlacementPackage::set_ship_data(std::vector<ShipData> ship_data) {
    this->ship_data = ship_data;
}

std::vector<ShipData> ShipPlacementPackage::get_ship_data() {
    return ship_data;
}
