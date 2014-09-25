#include "Ship.h"

// make a copy of the field list so it can't be manipulated from outside
Ship::Ship(std::list<std::shared_ptr<Field>> ship_parts)
    : ship_parts(ship_parts) {
}

bool Ship::is_destroyed() const {
    // check if each part/field has been hit
    for(auto it = ship_parts.begin(); it != ship_parts.end(); it++) {
        Field &ship_part = **it;
        if(!ship_part.is_hit()) {
            return false;
        }
    }
    return true;
}

unsigned int Ship::get_length() const {
    return ship_parts.size();
}


std::list<std::shared_ptr<Field>> Ship::get_ship_parts() const {
    // make a copy of the field list so it can't be manipulated from outside
    return ship_parts;
}
