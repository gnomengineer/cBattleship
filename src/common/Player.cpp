#include "Player.h"
#include <sstream>

Player::Player(std::string name)
    : name(name) {
}

Player::Player(int id)
    : Player(std::string("unnamed player #")) {
    std::stringstream ss;
    ss << id;
    name += ss.str();
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

BattleField &Player::get_battle_field() {
    return battle_field;
}

