#ifndef _GAMECONFIGURATION_H
#define _GAMECONFIGURATION_H

#include <common/packages/NetworkPackage.h>
#include <boost/program_options.hpp>

class GameConfiguration {
    private:
        bool hitspree;

    public:
        GameConfiguration();
        GameConfiguration(boost::program_options::variables_map &parameters);
        virtual ~GameConfiguration();
        
        bool get_hitspree();

        std::vector<unsigned char> to_bytes();
        void from_bytes(std::vector<unsigned char> &bytes, unsigned int index);
};


#endif /* _GAMECONFIGURATION_H */
