#ifndef _GAMECONFIGURATION_H
#define _GAMECONFIGURATION_H

#include <packages.pb.h>
#include <boost/program_options.hpp>

class GameConfiguration {
    private:
        bool hitspree;

    public:
        GameConfiguration();
        GameConfiguration(boost::program_options::variables_map &parameters);
        GameConfiguration(GameConfigurationPackage &game_configuration_package);
        virtual ~GameConfiguration();
        
        bool get_hitspree();

        void to_package(GameConfigurationPackage &package);
};


#endif /* _GAMECONFIGURATION_H */
