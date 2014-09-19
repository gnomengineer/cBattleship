#include "BattleField.h"

BattleField::BattleField() {
    for(int y = 0; y < BATTLEFIELD_WIDTH; y++) {
        for(int x = 0; x < BATTLEFIELD_HEIGHT; x++) {
            fields[y][x] = std::shared_ptr<Field>(new Field(position(y, x)));
        }
    }
}

void BattleField::add_ship(unsigned int length, orientation_t orientation, position_t position) {
    if(!is_valid_orientation(orientation)) throw std::invalid_argument("invalid orientation");
    if(!check_position(position, BATTLEFIELD_WIDTH, BATTLEFIELD_HEIGHT)) throw std::invalid_argument("position out of range");

    position_t endposition = position;
    endposition[orientation] += length;
    if(!check_position(endposition, BATTLEFIELD_WIDTH, BATTLEFIELD_HEIGHT)) throw std::invalid_argument("length out of range");
    
    std::list<std::shared_ptr<Field>> ship_parts;
    for(; position[orientation] < endposition[orientation]; position[orientation]++) {
        ship_parts.push_back(fields[position.y][position.x]);
    }

    ships.push_back(std::unique_ptr<Ship>(new Ship(ship_parts)));
}

bool BattleField::all_ships_destroyed() const {
    for(auto it = ships.begin(); it != ships.end() ; it++) {
        auto ship = **it;
        if(!ship.is_destroyed()) {
            return false;
        }
    }
    return true;
}
