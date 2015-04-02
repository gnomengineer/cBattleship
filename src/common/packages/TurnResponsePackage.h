#ifndef _TURNRESPONSEPACKAGE_H
#define _TURNRESPONSEPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class TurnResponsePackage : public NetworkPackage {
    private:
        bool valid;
        bool ship_hit;

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
};
#endif /* _TURNRESPONSEPACKAGE_H */
