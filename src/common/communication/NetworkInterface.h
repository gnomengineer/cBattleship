#ifndef _NETWORKINTERFACE_H
#define _NETWORKINTERFACE_H

#include <map>
#include <memory>
#include "NetworkCommand.h"

class NetworkInterface {
    private:
        std::map<command_nr_t, std::unique_ptr<NetworkCommand>> network_commands;

    public:
        NetworkInterface();
        std::vector<unsigned char> encode_command(NetworkCommand& command);
        NetworkCommand& decode_command(std::vector<unsigned char> command_data);

        void add_network_command(NetworkCommand* command);
};

#endif
