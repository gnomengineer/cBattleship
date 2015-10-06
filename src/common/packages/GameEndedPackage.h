#ifndef _GAMEENDEDPACKAGE_H
#define _GAMEENDEDPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class GameEndedPackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
            ar & this->won;
            ar & this->enemy_ships;
        }

        bool won;
        std::vector<ShipData> enemy_ships;

    public:
        GameEndedPackage() { }
        virtual ~GameEndedPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x83;
        }

        bool get_won() {
            return won;
        }

        void set_won(bool won) {
            this->won = won;
        }

        std::vector<ShipData> get_enemy_ships() {
            return enemy_ships;
        }

        void set_enemy_ships(std::vector<ShipData> enemy_ships) {
            this->enemy_ships = enemy_ships;
        }

};


#endif /* _GAMEENDEDPACKAGE_H */
