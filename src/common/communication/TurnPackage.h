#ifndef _TURNPACKAGE_H
#define _TURNPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class TurnPackage : public NetworkPackage {
    private:
        int pos_x;
        int pos_y;


    public:
        TurnPackage();
        ~TurnPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        int get_pos_x();
        void set_pos_x(int pos_x);
        int get_pos_y();
        void set_pos_y(int pos_y);

};
#endif /* _TURNPACKAGE_H */
