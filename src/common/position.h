#ifndef _POSITION_H
#define _POSITION_H

#include <utility>
#include <stdexcept>
#include <packages.pb.h>

typedef unsigned int position_coordinate_t;

// represents a 2 dimensional position
typedef struct position {
    public:
        position()
            : x(0), y(0) { }
        position(position_coordinate_t y, position_coordinate_t x)
            : x(x), y(y) { }
        position(const Position &pos) // convert from protobuf Message
            : x(pos.x()), y(pos.y()) { }
        position_coordinate_t y;
        position_coordinate_t x;

        position_coordinate_t& operator[](int index) {
            if(index == ORIENTATION_VERTICAL) return y;
            if(index == ORIENTATION_HORIZONTAL) return x;
            throw std::out_of_range("position::operator[]: position has only two dimensions. Valid values: 0, 1");

        }

        Position as_package() const {
            Position p;
            p.set_y(y);
            p.set_x(x);
            return p;
        }
} position_t;

bool check_position(position_t const &position, position_coordinate_t y, position_coordinate_t x);
bool is_valid_orientation(orientation_t orientation);

bool operator==(position_t position1, position_t position2);

#endif
