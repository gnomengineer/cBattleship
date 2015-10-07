#ifndef _GAMECONFIGURATIONPACKAGE_H
#define _GAMECONFIGURATIONPACKAGE_H

#include <vector>

#include <common/GameConfiguration.h>
#include "NetworkPackage.h"

class GameConfigurationPackage : public NetworkPackage {
    private:
        GameConfiguration config;

    public:
        GameConfigurationPackage();
        virtual ~GameConfigurationPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

        GameConfiguration get_config();
        void set_config(GameConfiguration config);
};
#endif /* _GAMECONFIGURATIONPACKAGE_H */
