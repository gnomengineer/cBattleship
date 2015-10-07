#ifndef _SERVERNETWORKPACKAGE_H
#define _SERVERNETWORKPACKAGE_H

#include <google/protobuf/message.h>

class ServerNetworkPackage {
    private:
        ::google::protobuf::Message &package;

    public:
        ServerNetworkPackage(::google::protobuf::Message &package);
        ::google::protobuf::Message &get_package();
};
#endif /* _SERVERNETWORKPACKAGE_H */
