#ifndef _BATTLEFIELD_H
#define _BATTLEFIELD_H

#include "Field.h"
#include "Ship.h"
#include <array>
#include <list>
#include <memory>

#define BATTLEFIELD_WIDTH 10
#define BATTLEFIELD_HEIGHT 10


// This class provides the functionality of a battle
// field. It gives methods for reading position of ships
class BattleField {
    private:
        std::array<std::array<std::shared_ptr<Field>, BATTLEFIELD_HEIGHT>, BATTLEFIELD_WIDTH> fields;
        std::list<std::unique_ptr<Ship>> ships;
        
    public:
        BattleField();
        void add_ship(unsigned int length, orientation_t orientation, position_t position);
        bool all_ships_destroyed() const;

    private:
        bool check_ship_collision(Ship &new_ship) const;
        bool check_ship_length_available(unsigned int length) const;
};

#endif 
