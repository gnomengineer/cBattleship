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
        static std::vector<unsigned char> encode_command(NetworkCommand& command);
        static NetworkCommand& decode_command(std::vector<unsigned char> command_data);

        static bool check_packaging(std::vector<unsigned char> command_data);
        static int get_package_size(std::vector<unsigned char> command_data);

        static void add_network_command(NetworkCommand* command);
};
 

class NetworkCommandListEnd {};

template<typename E, typename N> class NetworkCommandList {
    public:
       N next;
       NetworkCommandList() {
           NetworkInterface::add_network_command(new E());
       }
};

template<typename E> class NetworkCommandList<E, NetworkCommandListEnd> {
    public:
       NetworkCommandList() {
           NetworkInterface::add_network_command(new E());
       }
};

#define NETWORK_INTERFACE_COMMAND_LIST
#define NETWORK_INTERFACE_COMMAND(x)       NetworkCommandList<x,
#define NETWORK_INTERFACE_COMMAND_LIST_END NetworkCommandListEnd>> network_command_list;

extern NetworkInterface network_interface;

#endif
