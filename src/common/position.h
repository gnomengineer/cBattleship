#ifndef _POSITION_H
#define _POSITION_H

#include <utility>
#include <stdexcept>

typedef unsigned int position_coordinate_t;

typedef enum {
    ORIENTATION_VERTICAL   = 0, // maps to y coordinate on position_t
    ORIENTATION_HORIZONTAL = 1  // maps to x coordinate on position_t
} orientation_t;

// represents a 2 dimensional position
typedef struct position {
    position()
        : x(0), y(0) { }
    position(position_coordinate_t y, position_coordinate_t x)
        : x(x), y(y) { }
    position_coordinate_t y;
    position_coordinate_t x;

    position_coordinate_t& operator[](int index) {
        if(index == ORIENTATION_VERTICAL) return y;
        if(index == ORIENTATION_HORIZONTAL) return x;
        throw std::out_of_range("position::operator[]: position has only two dimensions. Valid values: 0, 1");

    }
} position_t;

bool check_position(position_t const &position, position_coordinate_t y, position_coordinate_t x);
bool is_valid_orientation(orientation_t orientation);

bool operator==(position_t position1, position_t position2);

#endif
