#ifndef _GAMECONFIGURATION_H
#define _GAMECONFIGURATION_H

#define DEFAULT_PORT ((unsigned short)13477)

namespace boost { namespace program_options { class variables_map; } }
class GameConfigurationPackage;

class GameConfiguration {
    private:
        bool hitspree;
        unsigned int size_y;
        unsigned int size_x;

    public:
        GameConfiguration();
        GameConfiguration(boost::program_options::variables_map &parameters);
        GameConfiguration(GameConfigurationPackage &game_configuration_package);
        virtual ~GameConfiguration();
        
        bool get_hitspree();

        unsigned int get_size_y();
        unsigned int get_size_x();

        void to_package(GameConfigurationPackage &package);
};


#endif /* _GAMECONFIGURATION_H */
