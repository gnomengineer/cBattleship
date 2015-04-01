#include "TurnPackage.h"

TurnPackage::TurnPackage() {
}

TurnPackage::~TurnPackage() {
}

package_nr_t TurnPackage::get_package_nr() {
    return 6;
}


std::vector<unsigned char> TurnPackage::encode_payload() {
    std::vector<unsigned char> encoded = AuthenticatedNetworkPackage::encode_payload();
    NetworkPackage::add_to_bytes(encoded, position.y, position.x);
    return encoded;
}

void TurnPackage::decode_payload(std::vector<unsigned char> command_data) {
    AuthenticatedNetworkPackage::decode_payload(command_data);
    NetworkPackage::get_from_bytes(command_data, IDENTITY_LENGTH, position.y, position.x);
}

void TurnPackage::set_position(position_t position) {
    this->position = position;
}

position_t TurnPackage::get_position() {
    return position;
}
