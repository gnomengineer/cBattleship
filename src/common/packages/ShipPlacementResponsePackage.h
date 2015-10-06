#ifndef _SHIPPLACEMENTRESPONSEPACKAGE_H
#define _SHIPPLACEMENTRESPONSEPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class ShipPlacementResponsePackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
            ar & this->valid;
            ar & this->out_of_bounds;
            ar & this->ships_overlap;
            ar & this->remaining_ships;
        }

        bool valid;
        bool out_of_bounds;
        bool ships_overlap;
        bool remaining_ships;

    public:
        ShipPlacementResponsePackage() { }
        virtual ~ShipPlacementResponsePackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x41;
        }

        bool get_valid() {
            return valid;
        }

        void set_valid(bool valid) {
            this->valid = valid;
        }

        bool get_out_of_bounds() {
            return out_of_bounds;
        }

        void set_out_of_bounds(bool out_of_bounds) {
            this->out_of_bounds = out_of_bounds;
        }

        bool get_ships_overlap() {
            return ships_overlap;
        }

        void set_ships_overlap(bool ships_overlap) {
            this->ships_overlap = ships_overlap;
        }

        bool get_remaining_ships() {
            return remaining_ships;
        }

        void set_remaining_ships(bool remaining_ships) {
            this->remaining_ships = remaining_ships;
        }

};


#endif /* _SHIPPLACEMENTRESPONSEPACKAGE_H */
