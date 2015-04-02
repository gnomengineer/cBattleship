#include "BattleField.h"
#include "Ship.h"

#include <algorithm>

BattleField::BattleField() {
    clear();
}

BattleField::BattleField(const BattleField& other) {
    fields = std::array<std::array<std::shared_ptr<Field>, BATTLEFIELD_WIDTH>, BATTLEFIELD_HEIGHT>(other.fields);
    ships = std::list<std::shared_ptr<Ship>>(other.ships);
    ships_available = std::map<unsigned int, int>(other.ships_available);
}

void BattleField::clear() {
    // fill battlefield with empty Field instances
    for(int y = 0; y < BATTLEFIELD_HEIGHT; y++) {
        for(int x = 0; x < BATTLEFIELD_WIDTH; x++) {
            fields[y][x] = std::shared_ptr<Field>(new Field(position(y, x)));
        }
    }

    ships.clear();

    //define possible ship lengths    
    ships_available.clear();
    ships_available[2] = 3;
    ships_available[3] = 2;
    ships_available[4] = 2;
    ships_available[5] = 1;
}

void BattleField::add_ship(unsigned int length, orientation_t orientation, position_t start_position) {
    if(!check_position(start_position, BATTLEFIELD_HEIGHT, BATTLEFIELD_WIDTH)) throw std::out_of_range("position out of range");
    if(ships_available[length] < 1) throw std::invalid_argument("no more ships of this length available");

    // check if length laps over the border of the battlefield
    position_t end_position = start_position;
    end_position[orientation] += length - 1;
    if(!check_position(end_position, BATTLEFIELD_HEIGHT, BATTLEFIELD_WIDTH)) throw std::out_of_range("length out of range");
    
    
    // check for collision of ships
    auto new_ship = std::shared_ptr<Ship>(new Ship(length, orientation, start_position, *this));
    if(!check_ship_collision(*new_ship)) throw std::invalid_argument("a field the ship uses is already taken by an other ship");

    // everythings ok with the ship, so use it
    ships.push_back(new_ship);
    ships_available[length]--;

    // mark the fields used by the ship as ship parts
    auto new_ship_parts = new_ship->get_ship_parts();
    for(auto it = new_ship_parts.begin(); it != new_ship_parts.end(); it++) {
        auto &new_ship_part = **it;
        new_ship_part.set_ship_part(true);
    }
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

bool BattleField::hit_field(position_t position) {
    auto hit_field = get_field(position);
    hit_field->set_hit();
    return hit_field->is_ship_part();
}

std::vector<std::vector<unsigned char>> BattleField::to_vector(bool hide_ships) {
    std::vector<std::vector<unsigned char>> result;
    result.resize(BATTLEFIELD_HEIGHT);
    for(int y = 0; y < BATTLEFIELD_HEIGHT; y++) {
        std::vector<unsigned char> row;
        row.resize(BATTLEFIELD_WIDTH);
        for(int x = 0; x < BATTLEFIELD_WIDTH; x++) {
            auto& field = *fields[y][x];
            if(field.is_hit()) {
                if(field.is_ship_part()) {
                    row[x] = FIELD_DESTROYED;
                } else {
                    row[x] = FIELD_HIT;
                }
            } else {
                if(field.is_ship_part() && !hide_ships) {
                    row[x] = FIELD_SHIP;
                } else {
                    row[x] = FIELD_WATER;
                }
            }
        }
        result[y] = row;
    }
    return result;
}

bool BattleField::check_ship_collision(Ship &new_ship) const {
    auto new_ship_parts = new_ship.get_ship_parts();
    for(auto it = new_ship_parts.begin(); it != new_ship_parts.end(); it++) {
        auto &new_ship_part = **it;
        if(new_ship_part.is_ship_part()) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<Field> BattleField::get_field(position_t position) {
    if(!check_position(position, BATTLEFIELD_HEIGHT, BATTLEFIELD_WIDTH)) throw std::out_of_range("position out of range");
    return fields[position.y][position.x];
}
std::vector<ShipData> BattleField::get_ship_data() const {
    std::vector<ShipData> ship_data;
    for(auto it = ships.begin(); it != ships.end(); it++) {
        ship_data.push_back((*it)->get_data());
    }
    return ship_data;
}

std::map<unsigned int, int> BattleField::get_ships_available() {
    return ships_available;
}

bool BattleField::all_ships_placed() {
    return std::all_of(ships_available.begin(), ships_available.end(), [](std::pair<unsigned int, int> pair) {
        const int number_available = pair.second;
        return number_available <= 0;
    });
}
