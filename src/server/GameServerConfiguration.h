#ifndef _GAMESERVERCONFIGURATION_H
#define _GAMESERVERCONFIGURATION_H

#include <string>
#include <common/GameConfiguration.h>
#define DEFAULT_BIND_ADDRESS "0.0.0.0"

class GameServerConfiguration : public GameConfiguration {
    private:
        std::string bind_address;
        unsigned short port;

    public:
        GameServerConfiguration();
        GameServerConfiguration(boost::program_options::variables_map &parameters);
        virtual ~GameServerConfiguration();

        std::string get_bind_address();
        unsigned short get_port();
};

#endif /* _GAMESERVERCONFIGURATION_H */
