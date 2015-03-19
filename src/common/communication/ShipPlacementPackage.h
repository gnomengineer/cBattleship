#ifndef _SHIPPLACEMENTPACKAGE_H
#define _SHIPPLACEMENTPACKAGE_H

#include <vector>
#include <common/position.h>

#include "AuthenticatedNetworkPackage.h"
class ShipPlacementPackage : public AuthenticatedNetworkPackage {
    private:
        std::vector<std::pair<unsigned int, orientation_t>> ships;


    public:
        ShipPlacementPackage();
        ~ShipPlacementPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::vector<std::pair<unsigned int, orientation_t>> get_ships();
        void set_ships(std::vector<std::pair<unsigned int, orientation_t>> ships);

};
#endif /* _SHIPPLACEMENTPACKAGE_H */
