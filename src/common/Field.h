#ifndef _FIELD_H
#define _FIELD_H

#include "position.h"

// represents a single field on the BattleField
// is also used to represent a part of the Ship
class Field {
    private:
        position_t position;
        bool hit;
        bool ship_part;

    public:
        Field(position_t position);

        position_t get_position() const;
        bool is_hit() const;
        void set_hit();
        bool is_ship_part() const;
        void set_ship_part(bool is_ship_part);
};
#endif

