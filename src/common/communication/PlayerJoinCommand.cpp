#include "PlayerJoinCommand.h"

std::vector<unsigned char> PlayerJoinCommand::encode_payload() {
    return std::vector<unsigned char>(player_name.begin(), player_name.end());
}

void PlayerJoinCommand::dencode_payload(std::vector<unsigned char> command_data) {
    player_name = std::string(command_data.begin(), command_data.end());
}

void PlayerJoinCommand::set_player_name(std::string player_name) {
    this->player_name = player_name;
}

std::string PlayerJoinCommand::get_player_name() {
    return player_name;
}
