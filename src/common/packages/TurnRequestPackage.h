#ifndef _TURNREQUESTPACKAGE_H
#define _TURNREQUESTPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class TurnRequestPackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
            ar & this->enemy_hit;
            ar & this->position;
        }

        bool enemy_hit;
        position_t position;

    public:
        TurnRequestPackage() { }
        virtual ~TurnRequestPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x41;
        }

        bool get_enemy_hit() {
            return enemy_hit;
        }

        void set_enemy_hit(bool enemy_hit) {
            this->enemy_hit = enemy_hit;
        }

        position_t get_position() {
            return position;
        }

        void set_position(position_t position) {
            this->position = position;
        }

};


#endif /* _TURNREQUESTPACKAGE_H */
