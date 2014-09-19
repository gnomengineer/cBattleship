#ifndef _FIELD_H
#define _FIELD_H

#include "position.h"

class Field {
    private:
        position_t position;
        bool hit;

    public:
        Field(position_t position);

        position_t get_position();
        bool is_hit();
        void set_hit();

};
#endif

