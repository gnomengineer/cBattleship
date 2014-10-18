#ifndef _NETWORKINTERFACE_H
#define _NETWORKINTERFACE_H

#include <map>
#include <memory>
#include "NetworkCommand.h"
#include "PlayerJoinCommand.h"
#include "PlayerJoinAnswerCommand.h"

class NetworkInterface {
    private:
        static std::map<command_nr_t, std::unique_ptr<NetworkCommand>> network_commands;

    public:
        NetworkInterface();
        static std::vector<unsigned char> encode_command(NetworkCommand& command);
        static NetworkCommand& decode_command(std::vector<unsigned char> command_data);

        static bool check_packaging(std::vector<unsigned char> command_data);
        static int get_package_size(std::vector<unsigned char> command_data);

        static void add_network_command(NetworkCommand* command);
};

#endif
