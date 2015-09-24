#include "GameServer.h"
#include <common/LogConfig.h>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/log/exceptions.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

namespace po = boost::program_options;

void print_header() {
    std::cout
    << "v0.1  __        __  __  __        __   _ " << std::setw(31) << ("built: "  __DATE__) << "\n"
    << " ____/ /  ___ _/ /_/ /_/ /__ ___ / /  (_)__    ___ ___ _____  _____ ____\n"
    << "/ __/ _ \\/ _ `/ __/ __/ / -_|_-</ _ \\/ / _ \\  (_-</ -_) __/ |/ / -_) __/\n"
    << "\\__/_.__/\\_,_/\\__/\\__/_/\\__/___/_//_/_/ .__/ /___/\\__/_/  |___/\\__/_/   \n"
    << "  by Troopa & Mogria           GPLv3 /_/ github.com/troopa/cBattleship  \n"
    << "This program comes with ABSOLUTELY NO WARRANTY; This is free software,\n"
    << "and you are welcome to redistribute it under certain conditions.\n"
    << std::endl;
}

template<typename T>
class cache {
    typedef T(*init_callback)();
    T cached;

    public:
        cache(init_callback initializer)
            : cached(initializer()) {
        }
         
        T& get() {
            return cached;
        }
};

po::options_description &get_common_options_description() {
    static cache<po::options_description> cached([]() {
        po::options_description desc("Common Options");
        desc.add_options()
            ("bind-address,b", po::value<std::string>()
                                   ->value_name("ip")
                                   ->default_value(DEFAULT_BIND_ADDRESS), "the address the server should bind to")
            ("port,p",         po::value<unsigned short>()
                                   ->value_name("port")
                                   ->default_value(DEFAULT_PORT),     "the port the server should listen to");
        return desc;
    });
    return cached.get();
}

po::options_description &get_config_file_options_description() {
    static cache<po::options_description> cached([]() {
        po::options_description desc("Configuration File Options");
        desc.add_options()
            ("game.hitspree",  po::value<bool>()
                                   ->value_name("bool")
                                   ->default_value(true),       "wheter a player can shoot again, if the last shot was a hit")
            ("board.sizex",    po::value<unsigned int>()
                                   ->value_name("uint")
                                   ->default_value(10u),        "the size of the gameboard (width)")
            ("board.sizey",    po::value<unsigned int>()
                                   ->value_name("uint")
                                   ->default_value(10u),        "the size of the gameboard (height)");
        desc.add(get_common_options_description());
        return desc;
    });
    return cached.get();

}



po::options_description &get_command_line_options_description() {
    static cache<po::options_description> cached([]() {
        po::options_description desc("Commandline Options");
        
        desc.add_options()
            ("help,h",                                          "Produce this help message")
            ("config-gen,G",  po::value<std::string>()
                                  ->value_name("file"),         "Overwrite the passed file with a sample configuration file, "
                                                                "with explanations for each option.")
            ("config,c",      po::value<std::vector<std::string>>()
                                  ->value_name("file")
                                  ->multitoken(),              "Read configuration from the specified file. "
                                                                "Multiple configuration files can be passed. "
                                                                "Every new configuration file overwrites the values set before. "
                                                                "Command line options always overwrite configuration file options. ")
        ;
        desc.add(get_common_options_description());
        return desc;
    });
    return cached.get();
}

po::variables_map parse_options(int argc, char *argv[]) {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, get_command_line_options_description()), vm);
    if(!vm["config"].empty()) {
        auto config_files = vm["config"].as<std::vector<std::string>>();
        for(auto it = config_files.begin(); it != config_files.end(); it++) {
            std::string config_file = *it;
            BOOST_LOG_TRIVIAL(info) << "parsing config file '" << config_file << "'";
            std::ifstream f(config_file);
            po::store(po::parse_config_file(f, get_config_file_options_description()), vm);
        }
    }
    po::notify(vm);
    return vm;
}

int print_help_message() {
    std::cout << get_command_line_options_description() << std::endl;
    return 1;
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
          << "# The address this server binds to. Leave it at 0.0.0.0 (default) so clients" << std::endl
          << "# can connect to the server from anywhere. If you change it to an other value" << std::endl
          << "# only clients that connect to this IP can connect. For example if you set it to" << std::endl
          << "# 127.0.0.1 only clients from localhost can connect. If you set it to something like" << std::endl
          << "# 192.168.1.40 only clients in your network can connnect." << std::endl
          << "#bind-address = 0.0.0.0" << std::endl
          << "" << std::endl
          << "# The TCP port which the server listens to." << std::endl
          << "# The default port is 13477" << std::endl
          << "#port = 13477" << std::endl
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
    try {
        LogConfig logConfig(std::string(argv[0]) + ".log", true);

        po::variables_map vm = parse_options(argc, argv);

        if(vm.count("help")) {
            return print_help_message();
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
    } catch(...) {
        std::cout << "Something the programmer didn't think about went horribly wrong. Sorry :-(" << std::endl;
        return 127;
    }
    return 0;
}
