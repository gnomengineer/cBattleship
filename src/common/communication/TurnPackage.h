#ifndef _TURNPACKAGE_H
#define _TURNPACKAGE_H

#include <vector>
#include <common/position.h>

#include "AuthenticatedNetworkPackage.h"
class TurnPackage : public AuthenticatedNetworkPackage {
    private:
        position_t position;

    public:
        TurnPackage();
        virtual ~TurnPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        position_t get_position();
        void set_position(position_t position);
};
#endif /* _TURNPACKAGE_H */
