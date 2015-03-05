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

template<typename T> package_nr_t get_package_nr_of() {
    package_nr_t package_nr = 0;
    {
        T package;
        package_nr = package.get_package_nr();
    }
    return package_nr;
}

template<typename T> bool is_package_of_type(NetworkPackage & package) {
    return get_package_nr_of<T>() == package.get_package_nr();
}

template<typename T> T & cast_package(NetworkPackage & package) {
    return *dynamic_cast<T*>(&package);
}

#endif
