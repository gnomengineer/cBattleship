#ifndef _NETWORKPACKAGE_H
#define _NETWORKPACKAGE_H

#include <vector>

typedef unsigned char package_nr_t;

class NetworkPackage {
    public:
        NetworkPackage() = default;
        virtual ~NetworkPackage() = default;
        virtual package_nr_t get_package_nr() = 0;
        virtual std::vector<unsigned char> encode_payload() = 0;
        virtual void decode_payload(std::vector<unsigned char> command_data) = 0;
};

#endif
