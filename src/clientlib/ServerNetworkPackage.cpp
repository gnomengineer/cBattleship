#include "ServerNetworkPackage.h"

ServerNetworkPackage::ServerNetworkPackage(::google::protobuf::Message &package)
    : package(package) {
}

::google::protobuf::Message &ServerNetworkPackage::get_package() {
    return package;
}
