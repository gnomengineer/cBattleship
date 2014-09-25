#include "Field.h"

Field::Field(position_t position)
    : position(position), hit(false) {
}

position_t Field::get_position() {
    return position;
}

bool Field::is_hit() {
    return hit;
}

void Field::set_hit() {
    hit = true;
}
