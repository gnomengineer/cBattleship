#ifndef _PLAYERJOINPACKAGE_H
#define _PLAYERJOINPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class PlayerJoinPackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
            ar & this->player_name;
        }

        std::string player_name;

    public:
        PlayerJoinPackage() { }
        virtual ~PlayerJoinPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x20;
        }

        std::string get_player_name() {
            return player_name;
        }

        void set_player_name(std::string player_name) {
            this->player_name = player_name;
        }

};


#endif /* _PLAYERJOINPACKAGE_H */
