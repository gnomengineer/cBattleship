#include "GameReadyPackage.h"

GameReadyPackage::GameReadyPackage() {
}

GameReadyPackage::~GameReadyPackage() {
}

package_nr_t GameReadyPackage::get_package_nr() {
    return 3;
}


std::vector<unsigned char> GameReadyPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    /* add the following members to the vector

     */
    return encoded;
}

void GameReadyPackage::decode_payload(std::vector<unsigned char> command_data) {
    /* retrieve the following members from the vector

     */
}


