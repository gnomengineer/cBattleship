#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <boost/program_options.hpp>
#include <string>
#include <memory>

namespace po = boost::program_options;

class Options {
    private:
        po::options_description common_options;
        po::options_description command_line_options;
        po::options_description config_file_options;
        
        std::vector<std::unique_ptr<po::variables_map>> variables;
    public:
        Options();
        virtual ~Options();
        po::variables_map &parse(int argc, char *argv[]);

        std::string get_help_message();
};

#endif /* _OPTIONS_H */
