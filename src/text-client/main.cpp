#include "TextClient.h"
#include "Options.h"
#include <common/Connection.h>
#include <common/LogConfig.h>

namespace po = boost::program_options;

void print_header() {
    std::cout << 
        "v0.1  __        __  __  __        __   _    \n"
        " ____/ /  ___ _/ /_/ /_/ /__ ___ / /  (_)__ \n"
        "/ __/ _ \\/ _ `/ __/ __/ / -_|_-</ _ \\/ / _ \\\n"
        "\\__/_.__/\\_,_/\\__/\\__/_/\\__/___/_//_/_/ .__/\n"
        "GPLv3  github.com/troopa/cBattleship /_/    \n"
        "  __          __        ___          __ \n"
        " / /______ __/ /_  ____/ (_)__ ___  / /_\n"
        "/ __/ -_) \\ / __/ / __/ / / -_) _ \\/ __/\n"
        "\\__/\\__/_\\_\\\\__/  \\__/_/_/\\__/_//_/\\__/\n"
        "by Troopa & Mogria " << std::setw(20) <<  ("built: " __DATE__) << "\n"
        "This program comes with ABSOLUTELY NO WARRANTY; This is free software,\n"
        "and you are welcome to redistribute it under certain conditions.\n"
        << std::endl;
}

int main(int argc, char *argv[]) {
    print_header();
    Options options;

    try {
        LogConfig logClient(std::string(argv[0]) + ".log");
        po::variables_map &vm = options.parse(argc, argv);

        if(argc < 2 || vm.count("help")) {
            std::cout << options.get_help_message() << std::endl;
            return 1;
        }

        TextClient textClient(vm["host"].as<std::string>(), vm["port"].as<unsigned short>());
        textClient.run();
    } catch(po::error &ex) {
        std::cout << "Error while parsing command line arguments: " <<  ex.what() << std::endl;
        return 125;
    } catch(std::runtime_error & ex) {
        std::cout << "error: " << ex.what() << std::endl;
        return 127;
    }

    return 0;
}

