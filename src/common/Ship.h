#ifndef _SHIP_H
#define _SHIP_H

#include "Field.h"
#include <list>
#include <memory>

// represents a single Ship on the BattleField
class Ship {
    private:
        std::list<std::shared_ptr<Field>> ship_parts;

    public:
        Ship(std::list<std::shared_ptr<Field>> ship_parts);

        bool is_destroyed() const;
        // length is determined by the number of parts added to the ship
        unsigned int get_length() const;

        std::list<std::shared_ptr<Field>> get_ship_parts() const;
};
#endif
