#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <common/communication/NetworkCommand.h>

namespace asio = boost::asio;

typedef struct read_command_handler {
    void operator()(std::vector<unsigned char> data) const;
} ReadCommandHandler;

class Connection {
    private:
        asio::streambuf buffer;
        asio::ip::tcp::socket socket;

    public:
        Connection(asio::ip::tcp::socket socket);

        void read(ReadCommandHandler handler);
        void write(std::vector<unsigned char> data);
};
#endif
