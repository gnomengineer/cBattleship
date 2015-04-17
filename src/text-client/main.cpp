#include <iostream>
#include <boost/asio.hpp>
#include <common/Connection.h>
#include <common/LogConfig.h>
#include "TextClient.h"

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

    try {
        TextClient textClient(argv[1]);
        textClient.run();
    } catch(std::runtime_error & ex) {
        std::cout << "error: " << ex.what() << std::endl;
    }

    return 0;
}

