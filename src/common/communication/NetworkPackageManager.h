#ifndef _NETWORKPACKAGEMANAGER_H
#define _NETWORKPACKAGEMANAGER_H

#include <map>
#include <tuple>
#include <memory>
#include "NetworkPackage.h"
#include "PlayerJoinPackage.h"
#include "PlayerJoinAnswerPackage.h"
#include "GameReadyPackage.h"
#include "PlayerReadyPackage.h"
#include "TurnRequestPackage.h"

class NetworkPackageManager {
    private:
        static std::map<package_nr_t, std::unique_ptr<NetworkPackage>> network_commands;

    public:
        NetworkPackageManager();

        std::vector<unsigned char> encode_command(NetworkPackage& command);
        NetworkPackage& decode_command(std::vector<unsigned char> command_data);

        bool check_packaging(std::vector<unsigned char> command_data);
        int get_package_size(std::vector<unsigned char> command_data);


        template<typename... Targs> void add_network_commands() {
            std::tuple<Targs...> tuple;
            add_network_command<0, Targs...>(tuple);
        }

        template<std::size_t I = 0,  typename... Tp>
        typename std::enable_if<I == sizeof...(Tp), void>::type
        add_network_command(std::tuple<Tp...> &) { // Unused arguments are given no names.
        }

        template<std::size_t I = 0, typename... Tp>
        typename std::enable_if<I < sizeof...(Tp), void>::type
        add_network_command(std::tuple<Tp...>& tuple) {
            using command_t = typename std::remove_reference<decltype(std::get<I>(tuple))>::type;
            std::unique_ptr<command_t> command(new command_t());
            network_commands[command->get_package_nr()] = std::move(command);
            add_network_command<I + 1, Tp...>(tuple);
        }

};

#endif
