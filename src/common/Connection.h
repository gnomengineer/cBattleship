#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <memory>

#include <common/NetworkPackageManager.h>
#include <common/conn_id.h>

#define DEFAULT_PORT ((unsigned short)13477)

namespace asio = boost::asio;

typedef std::function<void(std::shared_ptr<NetworkPackage> command)> ReadPackageHandler;
typedef std::function<void(int package_size)> ReadHeaderCommandHandler;
typedef std::function<void(const boost::system::error_code &err_code, std::size_t bytes_read)> ReadCallback;

class Connection {
    private:
        conn_id_t conn_id;
        std::vector<unsigned char> header;
        std::vector<unsigned char> payload;
        std::vector<unsigned char> writebuffer;
        asio::ip::tcp::socket socket;
        std::unique_ptr<NetworkPackageManager> network_package_manager;

        std::mutex read_lock;
        std::mutex write_lock;

    public:
        Connection(conn_id_t conn_id, asio::ip::tcp::socket socket);
        ~Connection();

        conn_id_t get_id();

        void read(ReadPackageHandler handler);
        void write(NetworkPackage& command);

        bool is_connected();
        void disconnect();

        template<typename T>
        void write(T& command) {
            write_lock.lock();
            writebuffer = network_package_manager->encode_package<T>(command);
            BOOST_LOG_TRIVIAL(debug) << "conn #" << conn_id << ": send package: " << debug_package(writebuffer);
            asio::async_write(socket, asio::buffer(writebuffer), [this](const boost::system::error_code& err_code, std::size_t bytes_written) {
                BOOST_LOG_TRIVIAL(debug) << "conn #" << conn_id << ": send " << bytes_written << " byte(s), err_code: " << err_code;
                write_lock.unlock();
            });
        }

    private:
        ReadCallback get_read_callback(ReadPackageHandler handler, int package_size);
        ReadCallback get_read_header_callback(ReadHeaderCommandHandler handler);

        template<typename T>
        std::string debug_package(T data, int num = -1) {
            std::stringstream ss;
            std::for_each(data.begin(), num == -1 ? data.end() : data.begin() + num, [&ss](unsigned char byte) {
                    ss << "$" << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
            });
            ss << std::dec;
            ss << std::setfill(' ');
            return ss.str();
        }
};
#endif
