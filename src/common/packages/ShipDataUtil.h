#ifndef SHIPDATAUTIL_H
#define SHIPDATAUTIL_H

#include <common/Ship.h>
#include "NetworkPackage.h"

class ShipDataUtil  {
    public:
        static void add_ship_to_bytes(std::vector<unsigned char> &bytes, ShipData ship) {
            unsigned char orientation = static_cast<unsigned char>(ship.orientation) & 1;
            NetworkPackage::add_to_bytes(bytes, ship.length, orientation, ship.start_position.y, ship.start_position.x);
        }

        static void add_ships_to_bytes(std::vector<unsigned char> &bytes, std::vector<ShipData> ships) {
            for(auto it = ships.begin(); it != ships.end(); it++) {
                add_ship_to_bytes(bytes, *it);
            }
        }

        static ShipData get_ship_from_bytes(std::vector<unsigned char> &bytes, unsigned int index) {
            ShipData ship;
            unsigned char orientation;
            NetworkPackage::get_from_bytes(bytes, index, ship.length, orientation, ship.start_position.y, ship.start_position.x);
            ship.orientation = static_cast<orientation_t>(orientation & 1);
            return ship;
        }

        static std::vector<ShipData> get_ships_from_bytes(std::vector<unsigned char> & bytes, unsigned int index) {
            const int ship_length = sizeof(unsigned int) + sizeof(unsigned char)
                                  + sizeof(position_coordinate_t) * 2;
            const int ships_length = bytes.size() - index;
            const int num_ships = ships_length / ship_length;

            std::vector<ShipData> result;
            for(int i = 0; i < num_ships; i++) {
                result.push_back(get_ship_from_bytes(bytes, index + i * ship_length));
            }
            return result;
        }
};

#endif /* SHIPDATAUTIL */
