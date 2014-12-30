#ifndef _NETWORKPACKAGEMANAGER_H
#define _NETWORKPACKAGEMANAGER_H

#include <map>
#include <memory>
#include "NetworkPackage.h"
#include "PlayerJoinCommand.h"
#include "PlayerJoinAnswerCommand.h"

class NetworkPackageManager {
    private:
        static std::map<package_nr_t, std::unique_ptr<NetworkPackage>> network_commands;

    public:
        static std::vector<unsigned char> encode_command(NetworkPackage& command);
        static NetworkPackage& decode_command(std::vector<unsigned char> command_data);

        static bool check_packaging(std::vector<unsigned char> command_data);
        static int get_package_size(std::vector<unsigned char> command_data);

        static void add_network_command(NetworkPackage* command);
};
 

class NetworkPackageListEnd {};

template<typename E, typename N> class NetworkPackageList {
    public:
       N next;
       NetworkPackageList() {
           NetworkPackageManager::add_network_command(new E());
       }
};

template<typename E> class NetworkPackageList<E, NetworkPackageListEnd> {
    public:
       NetworkPackageList() {
           NetworkPackageManager::add_network_command(new E());
       }
};

#define NETWORK_PACKAGE_MANAGER_COMMAND_LIST
#define NETWORK_PACKAGE_MANAGER_COMMAND(x)       NetworkPackageList<x,
#define NETWORK_PACKAGE_MANAGER_COMMAND_LIST_END NetworkPackageListEnd>> network_command_list;

extern NetworkPackageManager network_interface;

#endif
