#ifndef _SHIPPLACEMENTRESPONSEPACKAGE_H
#define _SHIPPLACEMENTRESPONSEPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class ShipPlacementResponsePackage : public NetworkPackage {
    private:
        bool valid;
        bool out_of_bounds;
        bool ships_overlap;
        int remaining_ships;

    public:
        ShipPlacementResponsePackage();
        virtual ~ShipPlacementResponsePackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

        bool get_valid();
        void set_valid(bool valid);
        bool get_out_of_bounds();
        void set_out_of_bounds(bool out_of_bounds);
        bool get_ships_overlap();
        void set_ships_overlap(bool ships_overlap);
        int get_remaining_ships();
        void set_remaining_ships(int remaining_ships);
};
#endif /* _SHIPPLACEMENTRESPONSEPACKAGE_H */
