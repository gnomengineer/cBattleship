#include "ShipPlacementPackage.h"
#include "ShipDataUtil.h"

ShipPlacementPackage::ShipPlacementPackage() {
}

ShipPlacementPackage::~ShipPlacementPackage() {
}

package_nr_t ShipPlacementPackage::get_package_nr() {
    return 4;
}


std::vector<unsigned char> ShipPlacementPackage::encode_payload() {
    std::vector<unsigned char> encoded = AuthenticatedNetworkPackage::encode_payload();
    ShipDataUtil::add_ships_to_bytes(encoded, ship_data);
    return encoded;
}

void ShipPlacementPackage::decode_payload(std::vector<unsigned char> package_data) {
    AuthenticatedNetworkPackage::decode_payload(package_data);
    ship_data = ShipDataUtil::get_ships_from_bytes(package_data, IDENTITY_LENGTH);
}

void ShipPlacementPackage::set_ship_data(std::vector<ShipData> ship_data) {
    this->ship_data = ship_data;
}

std::vector<ShipData> ShipPlacementPackage::get_ship_data() {
    return ship_data;
}
