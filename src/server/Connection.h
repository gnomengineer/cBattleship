#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <common/communication/NetworkCommand.h>

namespace asio = boost::asio;

typedef std::function<void(NetworkCommand& command)> ReadCommandHandler;
typedef std::function<void(int package_size)> ReadHeaderCommandHandler;
typedef std::function<void(const boost::system::error_code& err_code, std::size_t bytes_read)> ReadCallback;

class Connection {
    private:
        std::vector<unsigned char> header;
        std::vector<unsigned char> payload;
        asio::ip::tcp::socket socket;

        bool joined;

    public:
        Connection(asio::ip::tcp::socket socket);

        void read(ReadCommandHandler handler);
        void write(NetworkCommand& command);

        void set_joined(bool joined);
        bool get_joined();

    private:
        ReadCallback get_read_callback(ReadCommandHandler handler, int package_size);
        ReadCallback get_read_header_callback(ReadHeaderCommandHandler handler);
};
#endif
