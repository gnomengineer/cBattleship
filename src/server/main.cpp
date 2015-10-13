#include "GameServer.h"
#include "Options.h"
#include <common/LogConfig.h>
#include <boost/program_options.hpp>
#include <boost/log/exceptions.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

namespace po = boost::program_options;


void print_header() {
    std::cout << 
        "v0.1  __        __  __  __        __   _ " << std::setw(31) << ("built: "  __DATE__) << "\n"
        " ____/ /  ___ _/ /_/ /_/ /__ ___ / /  (_)__    ___ ___ _____  _____ ____\n"
        "/ __/ _ \\/ _ `/ __/ __/ / -_|_-</ _ \\/ / _ \\  (_-</ -_) __/ |/ / -_) __/\n"
        "\\__/_.__/\\_,_/\\__/\\__/_/\\__/___/_//_/_/ .__/ /___/\\__/_/  |___/\\__/_/   \n"
        "  by Troopa & Mogria           GPLv3 /_/ github.com/troopa/cBattleship  \n"
        "This program comes with ABSOLUTELY NO WARRANTY; This is free software,\n"
        "and you are welcome to redistribute it under certain conditions.\n"
        << std::endl;
}

int generate_configuration_file(std::string config_file) {
    {
        std::ifstream f(config_file);
        if(f.good()) {
            std::cerr << "Error: There already exists a file called '" << config_file << "' and I won't overwrite it." << std::endl;
            return 10;
        }
    }
    {
        std::ofstream f(config_file, std::ios_base::out | std::ios_base::trunc);
        f << "# Configuration file for the cbattleship-server" << std::endl
          << "# Every line preceded by a # is a comment" << std::endl
          << "" << std::endl
          << "# The address this server binds to. Leave it at " << DEFAULT_BIND_ADDRESS << " (default) so clients" << std::endl
          << "# can connect to the server from anywhere. If you change it to an other value" << std::endl
          << "# only clients that connect to this IP can connect. For example if you set it to" << std::endl
          << "# 127.0.0.1 only clients from localhost can connect. If you set it to something like" << std::endl
          << "# 192.168.1.40 only clients in your network can connnect." << std::endl
          << "#bind-address = " << DEFAULT_BIND_ADDRESS << std::endl
          << "" << std::endl
          << "# The TCP port which the server listens to." << std::endl
          << "# The default port is " << DEFAULT_PORT << std::endl
          << "#port = " << DEFAULT_PORT << std::endl
          << "" << std::endl
          << "[game]" << std::endl
          << "     # 0 = Every player gets to shoot once in an alternating fashion (default)" << std::endl
          << "     # 1 = Every Player gets to shoot as long as he misses. If he hits he can shoot again." << std::endl
          << "     #hitspree = 0" << std::endl
          << "" << std::endl
          << "[board]" << std::endl
          << "    # The following two options configure the size of the game board." << std::endl
          << "    # width of the game board (default 10)" << std::endl
          << "    #sizex = 10" << std::endl
          << "    # height of the game board (default 10)" << std::endl
          << "    #sizey = 10" << std::endl
          << "" << std::endl;

        std::cout << "Success: Generated configuration file '" << config_file << "'." << std::endl;
        return 0;
    }
}

int main(int argc, char *argv[]) {
    print_header();
    Options options;
    try {
        LogConfig logConfig(std::string(argv[0]) + ".log", true);
        po::variables_map &vm = options.parse(argc, argv);

        if(vm.count("help")) {
            std::cout << options.get_help_message() << std::endl;
            return 1;
        }

        if(!vm["config-gen"].empty()) {
            return generate_configuration_file(vm["config-gen"].as<std::string>());
        }

        GameServerConfiguration config(vm);
        GameServer server(config);
        server.run();
    } catch(po::error &ex) {
        std::cout << "Error while parsing command line arguments: " <<  ex.what() << std::endl;
        return 125;
    } catch(boost::log::runtime_error &ex) {
        std::cout << "A runtime exception in the logging subsystem occured: " <<  ex.what() << std::endl;
        return 125;
    } catch(boost::log::logic_error &ex) {
        std::cout << "Invalid usage or configuration of the logging subsystem: " <<  ex.what() << std::endl;
        return 126;
    } catch(std::runtime_error &ex) {
        std::cout << "Unexpected runtime error:" << ex.what() << std::endl;
        return 127;
    } catch(std::logic_error &ex) {
        std::cout << "Logic error:" << ex.what() << std::endl;
        return 127;
    } catch(boost::bad_any_cast &ex) {
        std::cout << "Couln't cast value: " << ex.what() << std::endl;
    } catch(std::exception &ex) {
        std::cout << "exception: " << ex.what() << std::endl;
    } catch(...) {
        std::cout << "Something the programmer didn't think about went horribly wrong. Sorry :-(" << std::endl;
        return 127;
    }
    return 0;
}
