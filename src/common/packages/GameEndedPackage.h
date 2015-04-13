#ifndef _GAMEENDEDPACKAGE_H
#define _GAMEENDEDPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
#include <common/Ship.h>

class GameEndedPackage : public NetworkPackage {
    private:
        bool won;
        std::vector<ShipData> enemy_ships;

    public:
        GameEndedPackage();
        virtual ~GameEndedPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

        bool get_won();
        void set_won(bool won);
        std::vector<ShipData> get_enemy_ships();
        void set_enemy_ships(std::vector<ShipData> enemy_ships);
};
#endif /* _GAMEENDEDPACKAGE_H */
