#ifndef _BATTLEFIELD_H
#define _BATTLEFIELD_H

#include "Field.h"
#include "Ship.h"
#include <array>
#include <list>
#include <map>
#include <memory>

#define BATTLEFIELD_WIDTH 10
#define BATTLEFIELD_HEIGHT 10


// This class provides the functionality of a battle
// field. It gives methods for reading position of ships
class BattleField {
    private:
        std::array<std::array<std::shared_ptr<Field>, BATTLEFIELD_HEIGHT>, BATTLEFIELD_WIDTH> fields;
        std::list<std::unique_ptr<Ship>> ships;
        //key: ship length, value: max ship quantity
        std::map<unsigned int, int> ships_available;
        
    public:
        BattleField();
        void add_ship(unsigned int length, orientation_t orientation, position_t position);
        bool all_ships_destroyed() const;
        void remove_ship(unsigned int length, orientation_t orientation, position_t position);

    private:
        bool check_ship_collision(Ship &new_ship) const;
};

#endif 
