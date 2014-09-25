#ifndef _POSITION_H
#define _POSITION_H

#include <utility>
#include <stdexcept>
typedef unsigned int position_coordinate_t;
typedef struct position {
    position(position_coordinate_t y, position_coordinate_t x)
        : x(x), y(y) { }
    position_coordinate_t y;
    position_coordinate_t x;

    position_coordinate_t& operator[](int index ) {
        if(index == 0) return y;
        if(index == 1) return x;
        throw std::out_of_range("position::operator[]: position has only two dimensions. Valid values: 0, 1");

    }
} position_t;

typedef enum {
    ORIENTATION_HORIZONTAL,
    ORIENTATION_VERTICAL
} orientation_t;

bool check_position(position_t const &position, position_coordinate_t y, position_coordinate_t x);
bool is_valid_orientation(orientation_t orientation);


#endif
