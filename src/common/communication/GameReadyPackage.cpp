#include "GameReadyPackage.h"

package_nr_t GameReadyPackage::get_package_nr() {
    return 3;
}


std::vector<unsigned char> GameReadyPackage::encode_payload() {
}

void GameReadyPackage::decode_payload(std::vector<unsigned char> command_data) {
}
