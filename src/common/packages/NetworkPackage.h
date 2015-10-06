#ifndef _NETWORKPACKAGE_H
#define _NETWORKPACKAGE_H

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <common/Ship.h>
#include <common/position.h>

typedef unsigned char package_nr_t;

class NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
        }

    public:
        NetworkPackage() { };
        virtual ~NetworkPackage() { };

        virtual package_nr_t get_package_nr() = 0;
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
    return dynamic_cast<T&>(package);
}

#endif
