#include "EnemyDisconnectedPackage.h"

EnemyDisconnectedPackage::EnemyDisconnectedPackage() {
}

EnemyDisconnectedPackage::~EnemyDisconnectedPackage() {
}

package_nr_t EnemyDisconnectedPackage::get_package_nr() {
    return 7;
}


std::vector<unsigned char> EnemyDisconnectedPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    /* add the following members to the vector
     */
    return encoded;
}

void EnemyDisconnectedPackage::decode_payload(std::vector<unsigned char> package_data) {
    /* retrieve the following members from the vector
     */
}

