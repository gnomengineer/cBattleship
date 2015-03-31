#include <iostream>
#include <boost/asio.hpp>
#include <common/communication/NetworkPackageManager.h>
#include <common/Connection.h>
#include "SimpleClient.h"

int main(int argc, char *argv[]){

    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <server>" << std::endl;
        return 1;
    }

    std::cout << "resolving ... " << std::endl;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(argv[1], "13477");
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, resolver.resolve(query));
    std::cout << "connecting ... " << std::endl;

    Connection connection(1, std::move(socket));
    PlayerJoinPackage player_join_package;

    try {
        SimpleClient client(connection);
        client.run();
        io_service.run();
    } catch(std::runtime_error & ex) {
        std::cout << "error: " << ex.what() << std::endl;
    }

    return 0;
}
