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
    for(int i = 0; i < ship_data.size(); i++) {
        ShipData &ship = ship_data[i];
        unsigned char orientation = ship.orientation & 1;
        NetworkPackage::add_to_bytes(encoded,
            ship.length, orientation,
            ship.start_position.y, ship.start_position.x);
    }
    return encoded;
}

void ShipPlacementPackage::decode_payload(std::vector<unsigned char> package_data) {
    AuthenticatedNetworkPackage::decode_payload(package_data);
    const int ship_length = sizeof(unsigned int) + sizeof(unsigned char)
                          + sizeof(position_coordinate_t) * 2;
    const int ships_length = package_data.size() - IDENTITY_LENGTH;
    const int num_ships = ships_length / ship_length;
    ship_data.clear();
    for(int i = 0; i < num_ships; i++) {
        ShipData ship;
        unsigned char orientation = 0;
        NetworkPackage::get_from_bytes(package_data, IDENTITY_LENGTH + i * ship_length,
            ship.length, orientation,
            ship.start_position.y, ship.start_position.x);
        ship.orientation = orientation & 1 ? ORIENTATION_HORIZONTAL : ORIENTATION_VERTICAL;
        ship_data.push_back(ship);
    }
}

void ShipPlacementPackage::set_ship_data(std::vector<ShipData> ship_data) {
    this->ship_data = ship_data;
}

std::vector<ShipData> ShipPlacementPackage::get_ship_data() {
    return ship_data;
}
