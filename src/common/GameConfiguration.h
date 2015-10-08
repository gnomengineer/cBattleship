#ifndef _GAMECONFIGURATION_H
#define _GAMECONFIGURATION_H

#include <boost/program_options.hpp>

class GameConfiguration {
    private:
        bool hitspree;

    public:
        GameConfiguration();
        GameConfiguration(boost::program_options::variables_map &parameters);
        virtual ~GameConfiguration();
        
        bool get_hitspree();
};


#endif /* _GAMECONFIGURATION_H */
