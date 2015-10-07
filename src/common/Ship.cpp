#include "Ship.h"
#include <algorithm>
#include "BattleField.h"

Ship::Ship(unsigned int length, orientation_t orientation, position_t start_position, BattleField &battle_field) {
    this->length = length;
    this->orientation = orientation;
    this->start_position = start_position;

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
    return std::all_of(ship_parts.begin(), ship_parts.end(), [](std::shared_ptr<Field> field) {
        return field->is_hit();
    });
}

unsigned int Ship::get_length() const {
    return length;
}


std::list<std::shared_ptr<Field>> Ship::get_ship_parts() const {
    // make a copy of the field list so it can't be manipulated from outside
    return ship_parts;
}

ShipData Ship::as_package() const {
    ShipData ship;
    ship.set_length(length);
    ship.set_orientation(orientation);
    ship.set_allocated_start_position(new Position(start_position.as_package()));
    return ship;
}
