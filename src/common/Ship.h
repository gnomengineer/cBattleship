#ifndef _SHIP_H
#define _SHIP_H

#include <list>
#include <memory>
#include "position.h"
#include <ShipData.pb.h>

class BattleField;
class Field;

// represents a single Ship on the BattleField
class Ship {
    private:
        std::list<std::shared_ptr<Field>> ship_parts;
        unsigned int length;
        orientation_t orientation;
        position_t start_position;
    public:
        Ship(unsigned int length, orientation_t orientation, position_t start_position, BattleField &battle_field);

        bool is_destroyed() const;
        // length is determined by the number of parts added to the ship
        unsigned int get_length() const;

        std::list<std::shared_ptr<Field>> get_ship_parts() const;
        void to_package(ShipData &ship) const;
};
#endif
