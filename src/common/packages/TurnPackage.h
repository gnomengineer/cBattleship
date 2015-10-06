#ifndef _TURNPACKAGE_H
#define _TURNPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "AuthenticatedNetworkPackage.h"

class TurnPackage : public AuthenticatedNetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<AuthenticatedNetworkPackage>(*this);
            ar & this->position;
        }

        position_t position;

    public:
        TurnPackage() { }
        virtual ~TurnPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x40;
        }

        position_t get_position() {
            return position;
        }

        void set_position(position_t position) {
            this->position = position;
        }

};


#endif /* _TURNPACKAGE_H */
