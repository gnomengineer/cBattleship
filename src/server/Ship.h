#ifndef _SHIP_H
#define _SHIP_H

#include "Field.h"
#include <list>

class Ship {
    private:
        // TODO: will cause problems if the field pointed to
        //       in this list gets deleted
        std::list<Field*> ship_parts;

    public:
        Ship(std::list<Field*> ship_parts);

        bool is_destroyed();
        unsigned int get_length();
};
#endif
