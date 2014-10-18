#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <common/communication/NetworkCommand.h>

namespace asio = boost::asio;

typedef std::function<void(NetworkCommand& command)> ReadCommandHandler;

class Connection {
    private:
        asio::streambuf buffer;
        asio::ip::tcp::socket socket;

        bool joined;

    public:
        Connection(asio::ip::tcp::socket socket);

        void read(ReadCommandHandler handler);
        void write(NetworkCommand& command);

        void set_joined(bool joined);
        bool get_joined();
};
#endif
