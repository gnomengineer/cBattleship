#ifndef _SHIPPLACEMENTPACKAGE_H
#define _SHIPPLACEMENTPACKAGE_H

#include <vector>
#include <common/Ship.h>

#include "AuthenticatedNetworkPackage.h"
class ShipPlacementPackage : public AuthenticatedNetworkPackage {
    private:
        std::vector<ShipData> ship_data;

    public:
        ShipPlacementPackage();
        virtual ~ShipPlacementPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::vector<ShipData> get_ship_data();
        void set_ship_data(std::vector<ShipData> ship_data);
};
#endif /* _SHIPPLACEMENTPACKAGE_H */
