#ifndef _BATTLEFIELD_H
#define _BATTLEFIELD_H

#include "Field.h"
#include "Ship.h"
#include <array>
#include <list>
#include <map>
#include <memory>
#include <vector>

#define BATTLEFIELD_WIDTH 10
#define BATTLEFIELD_HEIGHT 10

#define FIELD_WATER '~'
#define FIELD_SHIP 'S'
#define FIELD_HIT 'X'
#define FIELD_DESTROYED 'X'


// This class provides the functionality of a battle
// field. It gives methods for reading position of ships
class BattleField {
    private:
        std::array<std::array<std::shared_ptr<Field>, BATTLEFIELD_HEIGHT>, BATTLEFIELD_WIDTH> fields;
        std::list<std::shared_ptr<Ship>> ships;
        //key: ship length, value: max ship quantity
        std::map<unsigned int, int> ships_available;

    public:
        BattleField();
        BattleField(const BattleField& other);
        void add_ship(unsigned int length, orientation_t orientation, position_t position);
        bool all_ships_destroyed() const;
        bool hit_field(position_t position);

        void remove_ship(unsigned int length, orientation_t orientation, position_t position);

        std::vector<unsigned char> to_vector(bool hide_ships = false);

    private:
        bool check_ship_collision(Ship &new_ship) const;
};

#endif 
