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
        AuthenticatedNetworkPackage() { }
        virtual ~AuthenticatedNetworkPackage() { }

        std::string get_identity() {
            return identity;
        }

        void set_identity(std::string identity) {
            this->identity = identity;
        }

};
#endif /* _AUTHENTICATEDNETWORKPACKAGE_H */
