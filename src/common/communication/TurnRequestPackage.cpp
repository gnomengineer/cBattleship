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
    NetworkPackage::add_to_bytes(encoded, enemy_hit, position.y, position.x);
    return encoded;
}

void TurnRequestPackage::decode_payload(std::vector<unsigned char> command_data) {
    std::vector<unsigned char> encoded;
    NetworkPackage::get_from_bytes(command_data, 0, enemy_hit, position.y, position.x);
}

void TurnRequestPackage::set_enemy_hit(bool enemy_hit) {
    this->enemy_hit = enemy_hit;
}

bool TurnRequestPackage::get_enemy_hit() {
    return enemy_hit;
}
void TurnRequestPackage::set_position(position_t position) {
    this->position = position;
}

position_t TurnRequestPackage::get_position() {
    return position;
}
