#include "EnemyHitPackage.h"

EnemyHitPackage::EnemyHitPackage() {
}

EnemyHitPackage::~EnemyHitPackage() {
}

package_nr_t EnemyHitPackage::get_package_nr() {
    return 12;
}


std::vector<unsigned char> EnemyHitPackage::encode_payload() {
    std::vector<unsigned char> encoded;
    /* add the following members to the vector
     * - enemy_hit
     * - position
     */
    return encoded;
}

void EnemyHitPackage::decode_payload(std::vector<unsigned char> package_data) {
    /* retrieve the following members from the vector
     * - enemy_hit
     * - position
     */
}

void EnemyHitPackage::set_enemy_hit(bool enemy_hit) {
    this->enemy_hit = enemy_hit;
}

bool EnemyHitPackage::get_enemy_hit() {
    return enemy_hit;
}
void EnemyHitPackage::set_position(position_t position) {
    this->position = position;
}

position_t EnemyHitPackage::get_position() {
    return position;
}
