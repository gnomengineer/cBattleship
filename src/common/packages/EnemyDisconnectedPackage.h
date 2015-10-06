#ifndef _ENEMYDISCONNECTEDPACKAGE_H
#define _ENEMYDISCONNECTEDPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class EnemyDisconnectedPackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
        }


    public:
        EnemyDisconnectedPackage() { }
        virtual ~EnemyDisconnectedPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x81;
        }

};


#endif /* _ENEMYDISCONNECTEDPACKAGE_H */
