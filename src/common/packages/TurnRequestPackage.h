#ifndef _TURNREQUESTPACKAGE_H
#define _TURNREQUESTPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class TurnRequestPackage : public NetworkPackage {
    private:

    public:
        TurnRequestPackage();
        virtual ~TurnRequestPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

};
#endif /* _TURNREQUESTPACKAGE_H */
