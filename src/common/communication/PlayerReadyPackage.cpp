#include "PlayerReadyPackage.h"

PlayerReadyPackage::PlayerReadyPackage() {
}

PlayerReadyPackage::~PlayerReadyPackage() {
}

package_nr_t PlayerReadyPackage::get_package_nr() {
    return 4;
}


std::vector<unsigned char> PlayerReadyPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    /* add the following members to the vector

     */
    return encoded;
}

void PlayerReadyPackage::decode_payload(std::vector<unsigned char> command_data) {
    /* retrieve the following members from the vector

     */
}


