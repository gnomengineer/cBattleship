#include "PlayerJoinAnswerCommand.h"

command_nr_t PlayerJoinAnswerCommand::get_command_nr() {
    return 2;
}


std::vector<unsigned char> PlayerJoinAnswerCommand::encode_payload() {
    std::vector<unsigned char> encoded;
    encoded.push_back(static_cast<unsigned char>(accepted));
    encoded.insert(encoded.end(), identity.begin(), identity.end());
    return encoded;
}

void PlayerJoinAnswerCommand::decode_payload(std::vector<unsigned char> command_data) {
    accepted = !!command_data[0];
    identity = std::string(command_data.begin() + 1, command_data.end());
}

void PlayerJoinAnswerCommand::set_identity(std::string identity) {
    this->identity = identity;
}

std::string PlayerJoinAnswerCommand::get_identity() {
    return identity;
}

void PlayerJoinAnswerCommand::set_accepted(bool accepted) {
    this->accepted = accepted;
}

bool PlayerJoinAnswerCommand::get_accepted() {
    return accepted;
}
