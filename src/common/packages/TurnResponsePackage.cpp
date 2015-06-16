#include "TurnResponsePackage.h"

TurnResponsePackage::TurnResponsePackage()
    : valid(false), ship_hit(false), ship_of_length_destroyed(0) {
}

TurnResponsePackage::~TurnResponsePackage() {
}

package_nr_t TurnResponsePackage::get_package_nr() {
    return 8;
}


std::vector<unsigned char> TurnResponsePackage::encode_payload() {
    std::vector<unsigned char> encoded;
    NetworkPackage::add_to_bytes(encoded, valid, ship_hit, ship_of_length_destroyed);
    return encoded;
}

void TurnResponsePackage::decode_payload(std::vector<unsigned char> package_data) {
    NetworkPackage::get_from_bytes(package_data, 0, valid, ship_hit, ship_of_length_destroyed);
}

void TurnResponsePackage::set_valid(bool valid) {
    this->valid = valid;
}

bool TurnResponsePackage::get_valid() {
    return valid;
}

void TurnResponsePackage::set_ship_hit(bool ship_hit) {
    this->ship_hit = ship_hit;
}

bool TurnResponsePackage::get_ship_hit() {
    return ship_hit;
}

void TurnResponsePackage::set_ship_of_length_destroyed(int ship_of_length_destroyed) {
    this->ship_of_length_destroyed = ship_of_length_destroyed;
}

int TurnResponsePackage::get_ship_of_length_destroyed() {
    return ship_of_length_destroyed;
}
