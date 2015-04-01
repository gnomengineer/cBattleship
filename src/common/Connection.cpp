#include "Connection.h"

Connection::Connection(conn_id_t conn_id, asio::ip::tcp::socket socket)
    : conn_id(conn_id),
      header(3),
      payload(1024),
      writebuffer(1024),
      socket(std::move(socket)),
      read_lock(),
      write_lock() {


}

conn_id_t Connection::get_id() {
    return conn_id;
}

void Connection::read(ReadCommandHandler handler) {
    auto read_header_callback = [this, handler](int package_size) {
        payload.resize(package_size - 3);
        asio::async_read(socket, asio::buffer(payload, payload.size()), get_read_callback(handler, package_size));
    };
    read_lock.lock();
    asio::async_read(socket, asio::buffer(header, header.size()), get_read_header_callback(read_header_callback));
}

ReadCallback Connection::get_read_callback(ReadCommandHandler handler, int package_size) {
    return [this, handler, package_size](const boost::system::error_code& err_code, std::size_t bytes_read) {
        std::cout << "read " << bytes_read << " byte(s), err_code: " << err_code << ", package_size: " << package_size << std::endl;
        std::cout << "recv package: ";
        debug_print(payload, package_size - 3);
        std::cout << std::endl;
        if(!err_code && bytes_read >= package_size - 3) {
            std::vector<unsigned char> command(header.begin(), header.end());
            command.insert(command.end(), payload.begin(), payload.end());
            auto& network_command = network_package_manager.decode_command(command);
            read_lock.unlock();
            handler(network_command);
        } else {
            read_lock.unlock();
            disconnect();
        }
    };
}

ReadCallback Connection::get_read_header_callback(ReadHeaderCommandHandler handler) {
    return [this, handler](const boost::system::error_code& err_code, std::size_t bytes_read) {
        std::cout << "read " << bytes_read << " byte(s), err_code: " << err_code << std::endl;
        if(!err_code && bytes_read == 3) {
            int package_size = network_package_manager.get_package_size(header);
            std::cout << "read header, package(" << (int)header[0] << ") of size " << package_size << " incoming." << std::endl;
            std::cout << "recv package: ";
            debug_print(header);
            std::cout << std::endl;
            if(package_size != -1) {
                handler(package_size);
            } else {
                read_lock.unlock();
            }
                
        } else {
            read_lock.unlock();
            disconnect();
        }
    };
}

void Connection::write(NetworkPackage& command) {
    write_lock.lock();
    writebuffer = network_package_manager.encode_command(command);
    std::cout << "send package: ";
    debug_print(writebuffer);
    std::cout << std::endl;
    asio::async_write(socket, asio::buffer(writebuffer), [this](const boost::system::error_code& err_code, std::size_t bytes_written) {
        std::cout << "send " << bytes_written << " byte(s), err_code: " << err_code << std::endl;
        write_lock.unlock();
    });
}

bool Connection::is_connected() {
    return socket.is_open();
}

void Connection::disconnect() {
    boost::system::error_code ec;
    socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    socket.close();
}

