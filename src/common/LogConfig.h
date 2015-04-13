#ifndef LOGCONFIG_H
#define LOGCONFIG_H

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;

class LogConfig {
    public:
        LogConfig(std::string filename, bool to_console = false) {
            logging::add_common_attributes();
            logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");
            logging::add_file_log(filename, logging::keywords::format  = "[%TimeStamp%] %Severity%: %Message%", logging::keywords::auto_flush = true);
            if(to_console) logging::add_console_log(std::cout, logging::keywords::format  = "[%TimeStamp%] %Severity%: %Message%");

            logging::core::get()->set_filter
            (
                #ifdef NDEBUG
                    logging::trivial::severity >= logging::trivial::info
                #else
                    logging::trivial::severity >= logging::trivial::debug
                #endif
            );
        }
        ~LogConfig() {}
};
#endif /* LOGCONFIG_H */
