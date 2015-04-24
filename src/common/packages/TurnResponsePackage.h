#ifndef _TURNRESPONSEPACKAGE_H
#define _TURNRESPONSEPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class TurnResponsePackage : public NetworkPackage {
    private:
        bool valid;
        bool ship_hit;
        int ship_of_length_destroyed;

    public:
        TurnResponsePackage();
        virtual ~TurnResponsePackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

        bool get_valid();
        void set_valid(bool valid);
        bool get_ship_hit();
        void set_ship_hit(bool ship_hit);
        int get_ship_of_length_destroyed();
        void set_ship_of_length_destroyed(int ship_of_length_destroyed);
};
#endif /* _TURNRESPONSEPACKAGE_H */
