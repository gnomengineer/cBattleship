#include "position.h"

bool check_position(position_t const &position, position_coordinate_t y, position_coordinate_t x) {
    return position.y < y && position.x < x;
}

bool is_valid_orientation(orientation_t orientation) {
    return orientation == ORIENTATION_HORIZONTAL || orientation == ORIENTATION_VERTICAL;
}

bool operator==(position_t position1, position_t position2) {
    return position1.y == position2.y
        && position1.x == position2.x;
}

