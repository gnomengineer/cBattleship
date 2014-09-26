#include "BattleField.h"
#include <map>

BattleField::BattleField() {
    // fill battlefield with Field instances
    for(int y = 0; y < BATTLEFIELD_WIDTH; y++) {
        for(int x = 0; x < BATTLEFIELD_HEIGHT; x++) {
            fields[y][x] = std::shared_ptr<Field>(new Field(position(y, x)));
        }
    }

	//define possible ship lengths	
    ships_available[2] = 3;
    ships_available[3] = 2;
    ships_available[4] = 2;
    ships_available[5] = 1;
}

void BattleField::add_ship(unsigned int length, orientation_t orientation, position_t start_position) {
    if(!is_valid_orientation(orientation)) throw std::invalid_argument("invalid orientation");
    if(!check_position(start_position, BATTLEFIELD_WIDTH, BATTLEFIELD_HEIGHT)) throw std::out_of_range("position out of range");
    if(ships_available[length] < 1) throw std::invalid_argument("no more ships of this length available");

    // check if length laps over the border of the battlefield
    position_t end_position = start_position;
    end_position[orientation] += length - 1;
    if(!check_position(end_position, BATTLEFIELD_WIDTH, BATTLEFIELD_HEIGHT)) throw std::out_of_range("length out of range");
    
    // make a list of the fields the ship uses
    // and check for collision of ships
    std::list<std::shared_ptr<Field>> ship_parts;
    for(; start_position[orientation] <= end_position[orientation]; start_position[orientation]++) {
        ship_parts.push_back(fields[start_position.y][start_position.x]);
    }

    Ship new_ship(ship_parts);
    if(!check_ship_collision(new_ship)) throw std::invalid_argument("a field the ship uses is already taken by an other ship");

    // everythings ok with the ship, so use it
    ships.push_back(std::unique_ptr<Ship>(new Ship(ship_parts)));
	ships_available[legnth]--;
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

    // get a list of fields used by all other ships
    for(auto it = ships.begin(); it != ships.end(); it++) {
        auto ship = **it;
        used_fields.splice(used_fields.end(), ship.get_ship_parts());
    }

    auto new_ship_parts = new_ship.get_ship_parts();

    // check if the new ship uses a field already used by previously added ships
    for(auto it = used_fields.begin(); it != used_fields.end(); it++) {
        Field &used_field = **it;
        for(auto it = new_ship_parts.begin(); it != new_ship_parts.end(); it++) {
            Field &new_ship_part = **it;
            if(&used_field == &new_ship_part) {
                return false;
            }
        }
    }
    return true;
}

