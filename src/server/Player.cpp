#include "Player.h"
#include <sstream>
#include <common/Connection.h>
#include <common/BattleField.h>

Player::Player(Connection *connection)
    : name(std::string("unnamed player #")),
      connection(std::unique_ptr<Connection>(connection)),
      is_ready_to_start_(false),
      battle_field(nullptr) { 
    std::stringstream ss;
    ss << (long)connection->get_id();
    name += ss.str();
}

Connection & Player::get_connection() {
    return *connection;
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

bool Player::is_ready_to_start() {
    return is_ready_to_start_;
}

void Player::set_ready_to_start(bool ready_to_start) {
    is_ready_to_start_ = ready_to_start;
}

void Player::create_battle_field(GameConfiguration &config) {
    battle_field = std::unique_ptr<BattleField>(new BattleField(config));
}

BattleField &Player::get_battle_field() {
    return *battle_field;
}
