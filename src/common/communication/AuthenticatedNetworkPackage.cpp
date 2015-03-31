#include "AuthenticatedNetworkPackage.h"

AuthenticatedNetworkPackage::AuthenticatedNetworkPackage() {
}

AuthenticatedNetworkPackage::~AuthenticatedNetworkPackage() {
}

std::vector<unsigned char> AuthenticatedNetworkPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    encoded.insert(encoded.end(), identity.begin(), identity.end());
    return encoded;
}

void AuthenticatedNetworkPackage::decode_payload(std::vector<unsigned char> command_data) {
    identity = std::string(command_data.begin(), command_data.begin() + IDENTITY_LENGTH);
}

void AuthenticatedNetworkPackage::set_identity(std::string identity) {
    this->identity = identity;
}

std::string AuthenticatedNetworkPackage::get_identity() {
    return identity;
}
