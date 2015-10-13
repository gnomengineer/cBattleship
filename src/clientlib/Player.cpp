#include "Player.h"
#include <common/BattleField.h>
#include <sstream>

Player::Player()
    : battle_field(nullptr){
}


std::string Player::get_name() const {
    return name;
}

void Player::set_name(std::string new_name) {
    name = new_name;
}

std::string Player::get_identity() const {
    return identity;
}

void Player::set_identity(std::string new_identity) {
    identity = new_identity;
}

void Player::create_battle_field(unsigned int size_y, unsigned int size_x) {
    battle_field = std::unique_ptr<BattleField>(new BattleField(size_y, size_x));
}

BattleField &Player::get_battle_field() {
    return *battle_field;
}
