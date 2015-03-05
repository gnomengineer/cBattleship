#include "Player.h"
#include <sstream>

Player::Player(Connection & connection)
    : name(std::string("unnamed player #")), connection(connection) {
    std::stringstream ss;
    ss << (long)connection.get_id();
    name += ss.str();
}

Connection & Player::get_connection() {
    return connection;
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

