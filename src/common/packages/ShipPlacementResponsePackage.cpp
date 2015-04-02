#include "ShipPlacementResponsePackage.h"

ShipPlacementResponsePackage::ShipPlacementResponsePackage() {
}

ShipPlacementResponsePackage::~ShipPlacementResponsePackage() {
}

package_nr_t ShipPlacementResponsePackage::get_package_nr() {
    return 9;
}


std::vector<unsigned char> ShipPlacementResponsePackage::encode_payload() {
    std::vector<unsigned char> encoded;
    NetworkPackage::add_to_bytes(encoded, valid, out_of_bounds, ships_overlap, remaining_ships);
    return encoded;
}

void ShipPlacementResponsePackage::decode_payload(std::vector<unsigned char> package_data) {
    NetworkPackage::get_from_bytes(package_data, 0, valid, out_of_bounds, ships_overlap, remaining_ships);
}

void ShipPlacementResponsePackage::set_valid(bool valid) {
    this->valid = valid;
}

bool ShipPlacementResponsePackage::get_valid() {
    return valid;
}
void ShipPlacementResponsePackage::set_out_of_bounds(bool out_of_bounds) {
    this->out_of_bounds = out_of_bounds;
}

bool ShipPlacementResponsePackage::get_out_of_bounds() {
    return out_of_bounds;
}
void ShipPlacementResponsePackage::set_ships_overlap(bool ships_overlap) {
    this->ships_overlap = ships_overlap;
}

bool ShipPlacementResponsePackage::get_ships_overlap() {
    return ships_overlap;
}
void ShipPlacementResponsePackage::set_remaining_ships(int remaining_ships) {
    this->remaining_ships = remaining_ships;
}

int ShipPlacementResponsePackage::get_remaining_ships() {
    return remaining_ships;
}
