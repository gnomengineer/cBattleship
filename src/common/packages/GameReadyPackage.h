#ifndef _GAMEREADYPACKAGE_H
#define _GAMEREADYPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class GameReadyPackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
            ar & this->enemy_name;
        }

        std::string enemy_name;

    public:
        GameReadyPackage() { }
        virtual ~GameReadyPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x23;
        }

        std::string get_enemy_name() {
            return enemy_name;
        }

        void set_enemy_name(std::string enemy_name) {
            this->enemy_name = enemy_name;
        }

};


#endif /* _GAMEREADYPACKAGE_H */
