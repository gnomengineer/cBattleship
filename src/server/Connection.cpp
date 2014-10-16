#include "Connection.h"

Connection::Connection(asio::ip::tcp::socket socket)
    : buffer(1024),
      socket(std::move(socket)) {


}

void Connection::read(ReadCommandHandler handler) {
    asio::async_read(socket, buffer, [this, &handler](const boost::system::error_code& err_code, std::size_t bytes_read) {
        if(!err_code) {
            std::istream read_data(&buffer);
            std::vector<unsigned char> data((std::istreambuf_iterator<char>(read_data)),
                                            std::istreambuf_iterator<char>());
            handler(data);
        }
    });
}

void Connection::write(std::vector<unsigned char> data) {
    asio::async_write(socket, asio::buffer(data), [this](const boost::system::error_code& err_code, std::size_t bytes_written) {
    });
}

void ReadCommandHandler::operator()(std::vector<unsigned char> data) const {
}
