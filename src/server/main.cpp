#include "GameServer.h"
#include <common/LogConfig.h>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/log/exceptions.hpp>

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

po::options_description &get_command_line_options_description() {
    static bool configured = false;
    static po::options_description desc("Allowed options");

    if(!configured) {
        desc.add_options()
            ("help,h",                                         "produce this help message")
            ("bind-address,b", po::value<std::string>()
                                   ->value_name("ip")
                                   ->default_value("0.0.0.0"), "the address the server should bind to")
            ("port,p",         po::value<unsigned short>()
                                   ->value_name("port_number")
                                   ->default_value(13477),     "the port the server should listen to")
        ;
        configured = true;
    }

    return desc;
}

po::variables_map parse_command_line_options(int argc, char *argv[]) {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, get_command_line_options_description()), vm);
    po::notify(vm);
    return vm;
}

int main(int argc, char *argv[]) {
    print_header();
    try {
        LogConfig logConfig(std::string(argv[0]) + ".log", true);

        po::variables_map vm = parse_command_line_options(argc, argv);

        if(vm.count("help")) {
            std::cout << get_command_line_options_description() << "\n";
            return 1;
        }

        GameServer server(vm["bind-address"].as<std::string>(), vm["port"].as<unsigned short>());
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
