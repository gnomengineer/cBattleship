#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <common/packages/NetworkPackage.h>
#include <common/packages/NetworkPackageManager.h>
#include <iostream>
#include <iomanip>
#include <mutex>

namespace asio = boost::asio;

typedef std::function<void(NetworkPackage& command)> ReadCommandHandler;
typedef std::function<void(int package_size)> ReadHeaderCommandHandler;
typedef std::function<void(const boost::system::error_code& err_code, std::size_t bytes_read)> ReadCallback;
typedef int conn_id_t;

class Connection {
    private:
        conn_id_t conn_id;
        std::vector<unsigned char> header;
        std::vector<unsigned char> payload;
        std::vector<unsigned char> writebuffer;
        asio::ip::tcp::socket socket;
        NetworkPackageManager network_package_manager;

        std::mutex read_lock;
        std::mutex write_lock;

    public:
        Connection(conn_id_t conn_id, asio::ip::tcp::socket socket);

        conn_id_t get_id();

        void read(ReadCommandHandler handler);
        void write(NetworkPackage& command);

        bool is_connected();
        void disconnect();

    private:
        ReadCallback get_read_callback(ReadCommandHandler handler, int package_size);
        ReadCallback get_read_header_callback(ReadHeaderCommandHandler handler);

        template<typename T> void debug_print(T data, int num = -1) {
            std::for_each(data.begin(), num == -1 ? data.end() : data.begin() + num, [](unsigned char byte) {
                    std::cout << "$" << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
            });
            std::cout << std::dec;
            std::cout << std::setfill(' ');
        }
};
#endif
