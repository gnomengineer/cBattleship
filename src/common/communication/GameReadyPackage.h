#ifndef _GAMEREADYPACKAGE_H
#define _GAMEREADYPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class GameReadyPackage : public NetworkPackage {
    private:
        int field;


    public:
        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        int get_field();
        void set_field(int field);

};
#endif /* _GAMEREADYPACKAGE_H */
