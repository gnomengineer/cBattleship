#ifndef _BATTLEFIELD_H
#define _BATTLEFIELD_H

#include "Field.h"
#include <array>
#include <list>
#include <map>
#include <memory>
#include <vector>

#ifndef _SHIP_H
struct ShipData;
class Ship;
#endif

#define BATTLEFIELD_WIDTH 15
#define BATTLEFIELD_HEIGHT 10

#define FIELD_WATER '~'
#define FIELD_SHIP 'O'
#define FIELD_HIT 'X'
#define FIELD_DESTROYED '#'

#define PLAYER_NAME_MAX_LENGTH (BATTLEFIELD_WIDTH - 4)


// This class provides the functionality of a battle
// field. It gives methods for reading position of ships
class BattleField {
    private:
        std::array<std::array<std::shared_ptr<Field>, BATTLEFIELD_WIDTH>, BATTLEFIELD_HEIGHT> fields;
        std::list<std::shared_ptr<Ship>> ships;
        //key: ship length, value: max ship quantity
        std::map<unsigned int, int> ships_available;

    public:
        BattleField();
        BattleField(const BattleField& other);

        void clear();

        void add_ship(unsigned int length, orientation_t orientation, position_t position);
        bool all_ships_destroyed() const;
        bool hit_field(position_t position);

        void remove_ship(unsigned int length, orientation_t orientation, position_t position);

        std::vector<std::vector<unsigned char>> to_vector(bool hide_ships = false);

        std::shared_ptr<Field> get_field(position_t position);
        std::vector<ShipData> get_ship_data() const;

        std::map<unsigned int, int> get_ships_available();
        bool all_ships_placed();

    private:
        bool check_ship_collision(Ship &new_ship) const;
};

#endif 
