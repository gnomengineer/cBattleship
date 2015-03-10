#include "PlayerReadyPackage.h"

PlayerReadyPackage::PlayerReadyPackage() {
}

PlayerReadyPackage::~PlayerReadyPackage() {
}

package_nr_t PlayerReadyPackage::get_package_nr() {
    return 4;
}


std::vector<unsigned char> PlayerReadyPackage::encode_payload() {
    return AuthenticatedNetworkPackage::encode_payload();
}

void PlayerReadyPackage::decode_payload(std::vector<unsigned char> command_data) {
    AuthenticatedNetworkPackage::decode_payload(command_data);
}


