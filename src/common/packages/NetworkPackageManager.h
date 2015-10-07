#ifndef _NETWORKPACKAGEMANAGER_H
#define _NETWORKPACKAGEMANAGER_H

#include <map>
#include <memory>
#include <sstream>
#include "NetworkPackage.h"
#include "GameConfigurationPackage.h"
#include "PlayerJoinPackage.h"
#include "PlayerJoinAnswerPackage.h"
#include "GameReadyPackage.h"
#include "ShipPlacementPackage.h"
#include "ShipPlacementResponsePackage.h"
#include "TurnRequestPackage.h"
#include "TurnPackage.h"
#include "TurnResponsePackage.h"
#include "EnemyHitPackage.h"
#include "EnemyDisconnectedPackage.h"
#include "GameEndedPackage.h"

#define PACKAGE_TERMINATOR 0xCD

class NetworkPackageManager {
    private:
        static std::map<package_nr_t, std::unique_ptr<NetworkPackage>> network_commands;

    public:
        NetworkPackageManager();

        std::vector<unsigned char> encode_package(NetworkPackage &package);
        NetworkPackage& decode_package(std::vector<unsigned char> package_data);

        bool check_packaging(std::vector<unsigned char> package_data);
        int get_package_size(std::vector<unsigned char> package_data);


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


        template<typename T>
        std::vector<unsigned char> encode_package(T &package) {
            std::vector<unsigned char> encoded(3);
            encoded[0] = package.get_package_nr();

            std::ostringstream archive_stream;
            boost::archive::polymorphic_text_oarchive archive(archive_stream);
            archive << package;
            auto payload = archive_stream.str();
            encoded.insert(encoded.end(), payload.begin(), payload.end());
            encoded.push_back(PACKAGE_TERMINATOR);

            unsigned short size = encoded.size();
            encoded[1] = size & 0xFF;
            encoded[2] = (size >> 8) & 0xFF;

            return encoded;
        }

};

#endif
