#include <iostream>
#include <boost/asio.hpp>
#include <common/Connection.h>
#include <common/LogConfig.h>
#include "SimpleClient.h"

int main(int argc, char *argv[]){

    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <server>" << std::endl;
        return 1;
    }

    std::cout
    << "v0.1  __        __  __  __        __   _    \n"
    << " ____/ /  ___ _/ /_/ /_/ /__ ___ / /  (_)__ \n"
    << "/ __/ _ \\/ _ `/ __/ __/ / -_|_-</ _ \\/ / _ \\\n"
    << "\\__/_.__/\\_,_/\\__/\\__/_/\\__/___/_//_/_/ .__/\n"
    << "GPLv3  github.com/troopa/cBattleship /_/    \n"
    << "  __          __        ___          __ \n"
    << " / /______ __/ /_  ____/ (_)__ ___  / /_\n"
    << "/ __/ -_) \\ / __/ / __/ / / -_) _ \\/ __/\n"
    << "\\__/\\__/_\\_\\\\__/  \\__/_/_/\\__/_//_/\\__/\n"
    << "by Troopa & Mogria " << std::setw(20) <<  ("built: " __DATE__) << "\n"
    << "This program comes with ABSOLUTELY NO WARRANTY; This is free software,\n"
    << "and you are welcome to redistribute it under certain conditions.\n"
    << std::endl;

    LogConfig logClient(std::string(argv[0]) + ".log");

    std::cout << "trying to connect to '" << argv[1] << "' ... " << std::endl;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(argv[1], "13477");
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, resolver.resolve(query));
    std::cout << "trying to join server... " << std::endl;

    Connection connection(1, std::move(socket));
    try {
        SimpleClient client(connection);
        client.run();
        io_service.run();
    } catch(std::runtime_error & ex) {
        std::cout << "error: " << ex.what() << std::endl;
    }

    return 0;
}

