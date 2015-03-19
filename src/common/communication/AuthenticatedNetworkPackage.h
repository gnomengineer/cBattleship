#ifndef _AUTHENTICATEDNETWORKPACKAGE_H
#define _AUTHENTICATEDNETWORKPACKAGE_H

#include <vector>
#include <string>

#include "NetworkPackage.h"
#define IDENTITY_LENGTH 12
class AuthenticatedNetworkPackage : public NetworkPackage {
    private:
        std::string identity;

    public:
        AuthenticatedNetworkPackage();
        virtual ~AuthenticatedNetworkPackage();

        virtual package_nr_t get_package_nr() = 0;
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::string get_identity();
        void set_identity(std::string identity);
};
#endif /* _AUTHENTICATEDNETWORKPACKAGE_H */
