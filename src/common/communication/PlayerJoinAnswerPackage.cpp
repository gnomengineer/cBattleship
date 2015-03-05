#include "PlayerJoinAnswerPackage.h"

package_nr_t PlayerJoinAnswerPackage::get_package_nr() {
    return 2;
}


std::vector<unsigned char> PlayerJoinAnswerPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    encoded.insert(encoded.end(), identity.begin(), identity.end());
    return encoded;
}

void PlayerJoinAnswerPackage::decode_payload(std::vector<unsigned char> command_data) {
    identity = std::string(command_data.begin() + 1, command_data.end());
}

void PlayerJoinAnswerPackage::set_identity(std::string identity) {
    this->identity = identity;
}

std::string PlayerJoinAnswerPackage::get_identity() {
    return identity;
}
