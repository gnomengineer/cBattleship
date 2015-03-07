#include "TurnRequestPackage.h"

TurnRequestPackage::TurnRequestPackage() {
}

TurnRequestPackage::~TurnRequestPackage() {
}

package_nr_t TurnRequestPackage::get_package_nr() {
    return 5;
}


std::vector<unsigned char> TurnRequestPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    /* add the following members to the vector

     */
    return encoded;
}

void TurnRequestPackage::decode_payload(std::vector<unsigned char> command_data) {
    /* retrieve the following members from the vector

     */
}


