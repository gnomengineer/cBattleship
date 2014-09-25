#include "BattleField.h"
#include <map>

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
    if(!check_ship_length_available(length)) throw std::invalid_argument("no more ships of this length available");

    position_t endposition = position;
    endposition[orientation] += length;
    if(!check_position(endposition, BATTLEFIELD_WIDTH, BATTLEFIELD_HEIGHT)) throw std::invalid_argument("length out of range");
    
    std::list<std::shared_ptr<Field>> ship_parts;
    for(; position[orientation] < endposition[orientation]; position[orientation]++) {
        ship_parts.push_back(fields[position.y][position.x]);
    }

    Ship new_ship(ship_parts);
    if(!check_ship_collision(new_ship)) throw std::invalid_argument("a field the ship uses is already taken by an other ship");

    ships.push_back(std::unique_ptr<Ship>(new Ship(ship_parts)));
}

bool BattleField::all_ships_destroyed() const {
    for(auto it = ships.begin(); it != ships.end(); it++) {
        auto ship = **it;
        if(!ship.is_destroyed()) {
            return false;
        }
    }
    return true;
}

bool BattleField::check_ship_collision(Ship &new_ship) const {
    std::list<std::shared_ptr<Field>> used_fields;

    for(auto it = ships.begin(); it != ships.end(); it++) {
        auto ship = **it;
        used_fields.splice(used_fields.end(), ship.get_ship_parts());
    }

    auto new_ship_parts = new_ship.get_ship_parts();

    for(auto it = used_fields.begin(); it != used_fields.end(); it++) {
        auto used_field = **it;
        for(auto it = new_ship_parts.begin(); it != new_ship_parts.end(); it++) {
            auto new_ship_part = **it;
            if(&used_field == &new_ship_part) {
                return true;
            }
        }
    }
    return false;
}

bool BattleField::check_ship_length_available(unsigned int new_length) const {
    std::map<unsigned int, int> ships_available;
    ships_available[2] = 3;
    ships_available[3] = 2;
    ships_available[4] = 2;
    ships_available[5] = 1;
    for(auto it = ships.begin(); it != ships.end(); it++) {
        auto ship = **it;
        int ship_size = ship.get_ship_parts().size();
        ships_available[ship_size]--;
        if(ships_available[ship_size] < 0) return false;
    }

    return ships_available[new_length] >= 1;
}
