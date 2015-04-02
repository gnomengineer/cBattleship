#ifndef _GAMEREADYPACKAGE_H
#define _GAMEREADYPACKAGE_H

#include <vector>
#include <string>

#include "NetworkPackage.h"
class GameReadyPackage : public NetworkPackage {
    private:
        std::string enemy_name;

    public:
        GameReadyPackage();
        virtual ~GameReadyPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

        std::string get_enemy_name();
        void set_enemy_name(std::string enemy_name);
};
#endif /* _GAMEREADYPACKAGE_H */
