#include "Options.h"
#include <common/Connection.h>
#include <fstream>
#include <sstream>

Options::Options()
    : options("Allowed Options"),
      positional_options(),
      variables(nullptr) {
    options.add_options()
        ("help,h", "Produce this help message")
        ("host",   po::value<std::string>()
                       ->value_name("server"),
                       "the host to connect to (can be an IP as well as an hostname)")
        ("port,p", po::value<unsigned short>()
                       ->value_name("port")
                       ->default_value(DEFAULT_PORT),
                       "the port to connect to");
        ("bot",    po::value<std::string>()
                       ->value_name("bot_executable"),
                       "the bot executable");
    positional_options.add("bot", 1);
}

Options::~Options() {
}

po::variables_map &Options::parse(int argc, char *argv[]) {
    variables = std::unique_ptr<po::variables_map>(new po::variables_map());
    po::variables_map &vm = *variables;

    po::store(po::command_line_parser(argc, argv)
                  .options(options)
                  .positional(positional_options)
                  .run(), vm);
    po::notify(vm);

    return *variables;
}

std::string Options::get_help_message() {
    std::stringstream ss;
    ss << "Usage: cbattleship-text-client [--port port] [--host host] bot_executable\n\n";
    ss << options;
    return ss.str();
}
