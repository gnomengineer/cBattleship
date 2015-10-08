#ifndef _NETWORKPACKAGEMANAGER_H
#define _NETWORKPACKAGEMANAGER_H

#include <map>
#include <memory>
#include <sstream>
#include <packages.pb.h>

#define PACKAGE_TERMINATOR 0xCD
#define INVALID_PACKAGE_NR (-1)

typedef unsigned int package_nr_t;

class NetworkPackageManager {
    private:
        static std::map<package_nr_t, std::unique_ptr<::google::protobuf::Message>> network_packages;
        static std::map<size_t, package_nr_t> type_package_nr_map;

    public:
        NetworkPackageManager();
        virtual ~NetworkPackageManager();

        ::google::protobuf::Message &decode_package(std::vector<unsigned char> package_data);

        bool check_packaging(std::vector<unsigned char> package_data);
        int get_package_size(std::vector<unsigned char> package_data);

        template<typename... Targs> void add_network_packages() {
            std::tuple<Targs...> tuple;
            add_network_package<0, Targs...>(tuple);
        }

        template<std::size_t I = 0,  typename... Tp>
        typename std::enable_if<I == sizeof...(Tp), void>::type
        add_network_package(std::tuple<Tp...> &) { // Unused arguments are given no names.
        }

        template<std::size_t I = 0, typename... Tp>
        typename std::enable_if<I < sizeof...(Tp), void>::type
        add_network_package(std::tuple<Tp...>& tuple) {
            using package_t = typename std::remove_reference<decltype(std::get<I>(tuple))>::type;
            auto package = std::unique_ptr<::google::protobuf::Message>(new package_t);
            network_packages[I] = std::move(package);
            type_package_nr_map[typeid(package_t).hash_code()] = I;
            add_network_package<I + 1, Tp...>(tuple);
        }


    template<typename T>
    std::vector<unsigned char> encode_package(T &payload_package) {

        package_nr_t package_nr = get_package_nr<T>();
        if(package_nr == -1) throw std::invalid_argument("unknown package, can't encode it");

        std::vector<unsigned char> encoded(2);
        ::google::protobuf::Any *content = new ::google::protobuf::Any();
        content->PackFrom(payload_package);

        NetworkPackage network_package;
        network_package.set_package_nr(package_nr);
        network_package.set_allocated_content(content);

        std::string payload;
        network_package.SerializeToString(&payload);

        encoded.insert(encoded.end(), payload.begin(), payload.end());
        encoded.push_back(PACKAGE_TERMINATOR);

        unsigned short size = encoded.size();
        encoded[0] = size & 0xFF;
        encoded[1] = (size >> 8) & 0xFF;

        return encoded;
    }


    template<typename T>
    static package_nr_t get_package_nr() {
        using package_t = typename std::remove_reference<T>::type;
        size_t key = typeid(package_t).hash_code();
        if(type_package_nr_map.find(key) == type_package_nr_map.end()) {
            return INVALID_PACKAGE_NR;
        }

        return type_package_nr_map[key];
    }

};

template<typename T> bool is_package_of_type(NetworkPackage &package) {
    return NetworkPackageManager::get_package_nr<T>() == package.package_nr();
}

template<typename T> T & cast_package(NetworkPackage & package) {
    return dynamic_cast<T&>(package);
}

#endif