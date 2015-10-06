#ifndef _SHIP_H
#define _SHIP_H

#include "Field.h"
#include <list>
#include <memory>
#include <boost/serialization/access.hpp>
#include "position.h"

#ifndef _BATTLEFIELD_H
class BattleField;
#endif

struct ShipData {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & length;
            ar & orientation;
            ar & start_position;
        }

    public:
        unsigned int length;
        orientation_t orientation;
        position_t start_position;
};

// represents a single Ship on the BattleField
class Ship {
    private:
        std::list<std::shared_ptr<Field>> ship_parts;
        ShipData ship_data;
    public:

        Ship(ShipData ship_data, BattleField &battle_field);
        Ship(unsigned int length, orientation_t orientation, position_t start_position, BattleField &battle_field);

        bool is_destroyed() const;
        // length is determined by the number of parts added to the ship
        unsigned int get_length() const;

        std::list<std::shared_ptr<Field>> get_ship_parts() const;
        ShipData get_data() const;
};
#endif
