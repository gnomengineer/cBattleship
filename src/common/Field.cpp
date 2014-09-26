#include "Field.h"

Field::Field(position_t position)
    : position(position), hit(false) {
}

position_t Field::get_position() const {
    // return a copy of the position so it can't be manipulated
    return position;
}

bool Field::is_hit() const {
    return hit;
}

void Field::set_hit() {
    hit = true;
}
