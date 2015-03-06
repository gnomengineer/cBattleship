#ifndef _PLAYERREADYPACKAGE_H
#define _PLAYERREADYPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class PlayerReadyPackage : public NetworkPackage {
    private:


    public:
        PlayerReadyPackage();
        ~PlayerReadyPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);


};
#endif /* _PLAYERREADYPACKAGE_H */
