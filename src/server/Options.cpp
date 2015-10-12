#include "Options.h"
#include <boost/log/trivial.hpp>
#include <common/Connection.h>
#include "GameServerConfiguration.h"
#include <fstream>
#include <sstream>

Options::Options()
    : common_options("Common Options"),
      command_line_options("Commandline Options"),
      config_file_options("Configuration File Options") {
        common_options.add_options()
        ("bind-address,b", po::value<std::string>()
                               ->value_name("ip")
                               ->default_value(std::string(DEFAULT_BIND_ADDRESS)),
                               "the address the server should bind to")
        ("port,p",         po::value<unsigned short>()
                               ->value_name("port")
                               ->default_value(DEFAULT_PORT),
                               "the port the server should listen to");

    command_line_options.add_options()
        ("help,h", "Produce this help message")
        ("config-gen,G",  po::value<std::string>()
                              ->value_name("file"),
                              "Overwrite the passed file with a sample configuration file, "
                              "with explanations for each option.")
        ("config,c",      po::value<std::vector<std::string>>()
                              ->value_name("file")
                              ->multitoken(),
                              "Read configuration from the specified file. "
                              "Multiple configuration files can be passed. "
                              "Every new configuration file overwrites the values set before. "
                              "Command line options always overwrite configuration file options. ")
    ;
    command_line_options.add(common_options);

    config_file_options.add_options()
        ("game.hitspree",  po::value<bool>()
                               ->default_value(false),
                               "wheter a player can shoot again, if the last shot was a hit")
        ("board.sizex",    po::value<unsigned int>()
                               ->value_name("uint")
                               ->default_value(10),
                               "the size of the gameboard (width)")
        ("board.sizey",    po::value<unsigned int>()
                               ->value_name("uint")
                               ->default_value(10),
                               "the size of the gameboard (height)");
    config_file_options.add(common_options);

}

Options::~Options() {
}

po::variables_map &Options::parse(int argc, char *argv[]) {
    variables.clear();
    int index = 0;
    variables.push_back(std::unique_ptr<po::variables_map>(new po::variables_map()));
    po::variables_map &vm = *variables.at(index);

    // dummy positional arguments object
    // so an error is reported on the command line
    // when to many arguments are passed
    // See: https://stackoverflow.com/questions/3858251/parsing-positional-arguments
    po::positional_options_description positional_dummy;
    po::store(po::command_line_parser(argc, argv)
                  .options(command_line_options)
                  .positional(positional_dummy)
                  .run(), vm);
    po::notify(vm);

    if(vm["config"].empty()) {
        // store the default values for optoins defined
        // in the config file in the variables_map
        po::store(po::basic_parsed_options<char>(&config_file_options), vm);
    } else {
        auto config_files = vm["config"].as<std::vector<std::string>>();
        for(auto it = config_files.begin(); it != config_files.end(); it++) {
            std::string config_file = *it;
            BOOST_LOG_TRIVIAL(info) << "parsing config file '" << config_file << "'";

            variables.push_back(std::unique_ptr<po::variables_map>(new po::variables_map()));
            po::variables_map &prev = *variables.at(index);
            index++;
            po::variables_map &vm = *variables.at(index);

            std::ifstream f(config_file);
            po::store(po::parse_config_file(f, config_file_options), vm);
            po::notify(vm);

            prev.next(&vm);
        }
    }
    return vm;
            
}

std::string Options::get_help_message() {
    std::stringstream ss;
    ss << command_line_options;
    return ss.str();
}
