#ifndef _SHIP_H
#define _SHIP_H

#include "Field.h"
#include <list>
#include <memory>

class Ship {
    private:
        std::list<std::shared_ptr<Field>> ship_parts;

    public:
        Ship(std::list<std::shared_ptr<Field>> ship_parts);

        bool is_destroyed();
        unsigned int get_length();
};
#endif
