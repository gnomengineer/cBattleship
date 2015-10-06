#ifndef _TURNRESPONSEPACKAGE_H
#define _TURNRESPONSEPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class TurnResponsePackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
            ar & this->valid;
            ar & this->ship_hit;
            ar & this->ship_of_length_destroyed;
        }

        bool valid;
        bool ship_hit;
        int ship_of_length_destroyed;

    public:
        TurnResponsePackage() { }
        virtual ~TurnResponsePackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x43;
        }

        bool get_valid() {
            return valid;
        }

        void set_valid(bool valid) {
            this->valid = valid;
        }

        bool get_ship_hit() {
            return ship_hit;
        }

        void set_ship_hit(bool ship_hit) {
            this->ship_hit = ship_hit;
        }

        int get_ship_of_length_destroyed() {
            return ship_of_length_destroyed;
        }

        void set_ship_of_length_destroyed(int ship_of_length_destroyed) {
            this->ship_of_length_destroyed = ship_of_length_destroyed;
        }

};


#endif /* _TURNRESPONSEPACKAGE_H */
