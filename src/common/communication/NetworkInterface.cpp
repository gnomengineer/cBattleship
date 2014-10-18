#include "NetworkInterface.h"

#define PACKAGE_TERMINATOR 0xCD

NetworkInterface network_interface;
std::map<command_nr_t, std::unique_ptr<NetworkCommand>> NetworkInterface::network_commands;

NetworkInterface::NetworkInterface() {
    NetworkInterface::add_network_command(new PlayerJoinCommand());
    NetworkInterface::add_network_command(new PlayerJoinAnswerCommand());
}

std::vector<unsigned char> NetworkInterface::encode_command(NetworkCommand& command) {
    std::vector<unsigned char> encoded(3);
    encoded[0] = command.get_command_nr();

    auto payload = command.encode_payload();
    encoded.insert(encoded.end(), payload.begin(), payload.end());
    encoded.push_back(PACKAGE_TERMINATOR);

    unsigned short size = encoded.size();
    encoded[1] = size & 0xFF;
    encoded[2] = (size >> 8) & 0xFF;

    return encoded;
}

NetworkCommand& NetworkInterface::decode_command(std::vector<unsigned char> command_data) {
    if(!NetworkInterface::check_packaging(command_data)) throw std::runtime_error("frame is packaged incorrectly");
    unsigned char command_nr = command_data[0];
    int size = NetworkInterface::get_package_size(command_data);

    if(network_commands.find(command_data[0]) == network_commands.end()) throw std::runtime_error("invalid command nr");

    // remove terminator & header
    command_data.erase(command_data.begin() + (size - 1));
    command_data.erase(command_data.begin(), command_data.begin() + 3);

    auto& command = *network_commands[command_nr];
    command.decode_payload(command_data);

    return command;
}

bool NetworkInterface::check_packaging(std::vector<unsigned char> command_data) {
    int size = NetworkInterface::get_package_size(command_data);
    if(size == -1) return false;
    if(size < 4) return false;
    if(command_data.size() >= size) return false;
    if(command_data[size - 1] != PACKAGE_TERMINATOR) return false;
    return true;
}

int NetworkInterface::get_package_size(std::vector<unsigned char> command_data) {
    if(command_data.size() < 4) return -1;
    unsigned short size = 0;
    size |= command_data[1];
    size |= command_data[2] << 8;
    return size;
}

void NetworkInterface::add_network_command(NetworkCommand* command) {
    network_commands[command->get_command_nr()] = std::unique_ptr<NetworkCommand>(command);
}

