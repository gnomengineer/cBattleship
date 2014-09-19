#include "Ship.h"

// make  a copy so the field list can't be manipulated from outside
Ship::Ship(std::list<std::shared_ptr<Field>> ship_parts)
    : ship_parts(ship_parts) {
}

bool Ship::is_destroyed() {
    for(auto it = ship_parts.begin(); it != ship_parts.end(); it++) {
        auto ship_part = *it;
        if(!ship_part->is_hit()) {
            return false;
        }
    }
    return true;
}

unsigned int Ship::get_length() {
    return ship_parts.size();
}
