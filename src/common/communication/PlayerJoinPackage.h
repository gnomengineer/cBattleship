#ifndef _PLAYERJOINPACKAGE_H
#define _PLAYERJOINPACKAGE_H

#include <string>
#include <vector>

#include "NetworkPackage.h"
class PlayerJoinPackage : public NetworkPackage {
    private:
        std::string player_name;

    public:
        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::string get_player_name();
        void set_player_name(std::string player_name);
};
#endif 
