#ifndef _BATTLEFIELD_H
#define _BATTLEFIELD_H

#include "position.h"

#include <list>
#include <map>
#include <memory>
#include <vector>
#include <ShipData.pb.h>

class Ship;
class Field;
class GameConfiguration;

#define FIELD_WATER '~'
#define FIELD_SHIP 'O'
#define FIELD_HIT 'X'
#define FIELD_DESTROYED '#'

#define PLAYER_NAME_MAX_LENGTH (16)


// This class provides the functionality of a battle
// field. It gives methods for reading position of ships
class BattleField {
    private:
        unsigned int size_y;
        unsigned int size_x;

        std::vector<std::vector<std::shared_ptr<Field> > > fields;
        std::list<std::shared_ptr<Ship> > ships;
        //key: ship length, value: max ship quantity
        std::map<unsigned int, unsigned int> ships_available;

    public:
        BattleField(GameConfiguration &config);
        BattleField(const BattleField& other);

        unsigned int get_size_y() const;
        unsigned int get_size_x() const;

        void add_ship(unsigned int length, orientation_t orientation, position_t position);
        bool all_ships_destroyed() const;
        bool hit_field(position_t position);

        void remove_ship(unsigned int length, orientation_t orientation, position_t position);

        std::vector<std::vector<unsigned char>> to_vector(bool hide_ships = false);

        std::shared_ptr<Field> get_field(position_t position);
        std::vector<ShipData> get_ship_data() const;

        void add_ship_data(std::vector<ShipData> ship_data);

        std::map<unsigned int, unsigned int> get_ships_available();
        bool all_ships_placed();

        std::shared_ptr<Ship> get_ship_at_position(position_t position);

    private:
        bool check_ship_collision(Ship &new_ship) const;
};

#endif 
