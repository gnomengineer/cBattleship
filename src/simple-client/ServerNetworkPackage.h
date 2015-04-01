#ifndef _SERVERNETWORKPACKAGE_H
#define _SERVERNETWORKPACKAGE_H

#include <common/packages/NetworkPackage.h>
class ServerNetworkPackage {
    private:
        NetworkPackage &package;

    public:
        ServerNetworkPackage(NetworkPackage &package);
        NetworkPackage &get_package();
};
#endif /* _SERVERNETWORKPACKAGE_H */
