#ifndef _SHIPPLACEMENTPACKAGE_H
#define _SHIPPLACEMENTPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "AuthenticatedNetworkPackage.h"

class ShipPlacementPackage : public AuthenticatedNetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<AuthenticatedNetworkPackage>(*this);
            ar & this->ship_data;
        }

        std::vector<ShipData> ship_data;

    public:
        ShipPlacementPackage() { }
        virtual ~ShipPlacementPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x40;
        }

        std::vector<ShipData> get_ship_data() {
            return ship_data;
        }

        void set_ship_data(std::vector<ShipData> ship_data) {
            this->ship_data = ship_data;
        }

};


#endif /* _SHIPPLACEMENTPACKAGE_H */
