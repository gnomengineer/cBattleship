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
        virtual void decode_payload(std::vector<unsigned char> package_data) = 0;

        // utility methods
        template<typename T>
        static std::vector<unsigned char> to_bytes(T value) {
            std::vector<unsigned char> result(sizeof(T));
            for(int i = 0; i < sizeof(T); i++) {
                result[sizeof(T) - i - 1] = value >> (i*8) & 0xFF;
            }
            return result;
        }

        template<typename T>
        static T from_bytes(std::vector<unsigned char> &bytes, unsigned int index) {
            T result = T();
            for(int i = 0; i < sizeof(T); i++) {
                result |= bytes[index + i] << ((sizeof(T) - i - 1)*8);
            };
            return result;
        }

        
        template<typename... Targs>
        static void add_to_bytes(std::vector<unsigned char> &bytes, Targs... values) {
            std::vector<unsigned char> results[] = {std::vector<unsigned char>(), (to_bytes<Targs>(values))...};
            for(int i = 0; i < sizeof...(Targs); i++) {
                bytes.insert(bytes.end(), results[i + 1].begin(), results[i + 1].end());
            }
        }

        template<typename... Targs>
        static void get_from_bytes(std::vector<unsigned char> &bytes, unsigned int index, Targs&... values) {
            int _[] = {0, (values = from_bytes<Targs>(bytes, (index += sizeof(Targs)) - sizeof(Targs)), 0)...};
            (void)_;
        }
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
