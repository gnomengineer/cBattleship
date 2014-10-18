#include "Connection.h"
#include <common/communication/NetworkInterface.h>

Connection::Connection(asio::ip::tcp::socket socket)
    : buffer(1024),
      socket(std::move(socket)) {


}

void Connection::read(ReadCommandHandler handler) {
    std::function<void(const boost::system::error_code& err_code, std::size_t bytes_read)> read_handler;
    read_handler = [this, read_handler, &handler](const boost::system::error_code& err_code, std::size_t bytes_read) {
        std::cout << "read " << bytes_read << " from client, err_code: " << err_code << std::endl;
        if(!err_code) {
            std::istream read_data(&buffer);
            std::vector<unsigned char> data((std::istreambuf_iterator<char>(read_data)),
                                            std::istreambuf_iterator<char>());
            handler(NetworkInterface::decode_command(data));
        }

        asio::async_read(socket, buffer, read_handler);
    };
    asio::async_read(socket, buffer, read_handler);
}

void Connection::write(NetworkCommand& command) {
    auto data = NetworkInterface::encode_command(command);
    asio::async_write(socket, asio::buffer(data), [this](const boost::system::error_code& err_code, std::size_t bytes_written) {
    });
}

void Connection::set_joined(bool joined) {
    this->joined = joined;
}

bool Connection::get_joined() {
    return joined;
}
