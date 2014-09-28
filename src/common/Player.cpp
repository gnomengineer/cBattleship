#include "Player.h"

Player::Player(std::string name)
    : name(name) {
}

std::string Player::get_name() const {
    return name;
}

std::string Player::get_identity() const {
    return identity;
}

void Player::set_identity(std::string new_identity) {
    identity = new_identity;
}

BattleField &Player::get_battle_field() {
    return battle_field;
}

