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
        NetworkPackage::add_to_bytes(encoded,
            ship.length, ship.orientation,
            ship.start_position.y, ship.start_position.x);
    }
    return encoded;
}

void ShipPlacementPackage::decode_payload(std::vector<unsigned char> package_data) {
    AuthenticatedNetworkPackage::decode_payload(package_data);
    const int ship_length = 4;
    const int ships_length = package_data.size() - IDENTITY_LENGTH;
    const int num_ships = ship_length / ship_length;
    ship_data.clear();
    for(int i = 0; i < num_ships; i++) {
        ShipData ship;
        NetworkPackage::get_from_bytes(package_data, IDENTITY_LENGTH + i * 4,
            ship.length, (unsigned char &)ship.orientation,
            ship.start_position.y, ship.start_position.x);
        ship_data.push_back(ship);
    }
}

void ShipPlacementPackage::set_ship_data(std::vector<ShipData> ship_data) {
    this->ship_data = ship_data;
}

std::vector<ShipData> ShipPlacementPackage::get_ship_data() {
    return ship_data;
}
