#ifndef _PLAYERREADYPACKAGE_H
#define _PLAYERREADYPACKAGE_H

#include <vector>

#include "AuthenticatedNetworkPackage.h"
class PlayerReadyPackage : public AuthenticatedNetworkPackage {
    private:


    public:
        PlayerReadyPackage();
        virtual ~PlayerReadyPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

};
#endif /* _PLAYERREADYPACKAGE_H */
