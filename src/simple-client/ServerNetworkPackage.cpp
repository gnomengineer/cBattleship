#include "ServerNetworkPackage.h"

ServerNetworkPackage::ServerNetworkPackage(NetworkPackage &package)
    : package(package) {
}

NetworkPackage &ServerNetworkPackage::get_package() {
    return package;
}
