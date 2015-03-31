#include "Ship.h"
#include "BattleField.h"

Ship::Ship(ShipData ship_data, BattleField &battle_field)
    : Ship(ship_data.length, ship_data.orientation, ship_data.start_position, battle_field) {
}

Ship::Ship(unsigned int length, orientation_t orientation, position_t start_position, BattleField &battle_field) {
    ship_data.length = length;
    ship_data.orientation = orientation;
    ship_data.start_position = start_position;

    if(!is_valid_orientation(orientation)) throw std::invalid_argument("invalid orientation");

    // make a list of the fields the ship uses
    position_t end_position = start_position;
    end_position[orientation] += length - 1;
    for(; start_position[orientation] <= end_position[orientation]; start_position[orientation]++) {
        ship_parts.push_back(battle_field.get_field(start_position));
    }

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
    return ship_data.length;
}


std::list<std::shared_ptr<Field>> Ship::get_ship_parts() const {
    // make a copy of the field list so it can't be manipulated from outside
    return ship_parts;
}

ShipData Ship::get_data() const {
    return ship_data;
}
