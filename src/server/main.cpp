#include "GameServer.h"
#include "LogConfig.h"

int main(int argc, char *argv[]) {
    std::cout
    << "v0.1  __        __  __  __        __   _ " << std::setw(32) << ("built on "  __DATE__) << "\n"
    << " ____/ /  ___ _/ /_/ /_/ /__ ___ / /  (_)__    ___ ___ _____  _____ ____\n"
    << "/ __/ _ \\/ _ `/ __/ __/ / -_|_-</ _ \\/ / _ \\  (_-</ -_) __/ |/ / -_) __/\n"
    << "\\__/_.__/\\_,_/\\__/\\__/_/\\__/___/_//_/_/ .__/ /___/\\__/_/  |___/\\__/_/   \n"
    << "  by Troopa & Mogria           GPLv3 /_/ github.com/troopa/cBattleship  \n"
    << "This program comes with ABSOLUTELY NO WARRANTY; This is free software,\n"
    << "and you are welcome to redistribute it under certain conditions."
    << std::endl;

    LogConfig logConfig(std::string(argv[0]) + ".log");
    GameServer server;
    server.run();
    return 0;
}
