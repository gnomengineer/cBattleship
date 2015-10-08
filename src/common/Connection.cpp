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

Connection::~Connection() {
    disconnect();
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
        BOOST_LOG_TRIVIAL(debug) << "conn #" << conn_id << ": read " << bytes_read << " byte(s), err_code: " << err_code << ", package_size: " << package_size;
        BOOST_LOG_TRIVIAL(debug) << "conn #" << conn_id << ": recv package: " << debug_package(payload, package_size - 3);
        if(!err_code && bytes_read >= package_size - 3) {
            std::vector<unsigned char> command(header.begin(), header.end());
            command.insert(command.end(), payload.begin(), payload.end());
            auto network_command = network_package_manager.decode_package(command);
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
        BOOST_LOG_TRIVIAL(debug) << "conn #" << conn_id << ": read " << bytes_read << " byte(s), err_code: " << err_code;
        if(!err_code && bytes_read == 3) {
            int package_size = network_package_manager.get_package_size(header);
            BOOST_LOG_TRIVIAL(debug) << "conn #" << conn_id << ": read header, package(" << (int)header[0] << ") of size " << package_size << " incoming.";
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

bool Connection::is_connected() {
    return socket.is_open();
}

void Connection::disconnect() {
    // wait until everything is written ...
    std::lock_guard<std::mutex> l2(write_lock);
    if(!is_connected()) return;
    boost::system::error_code ec;
    BOOST_LOG_TRIVIAL(debug) << "shutting down connection #" << conn_id;
    socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    BOOST_LOG_TRIVIAL(debug) << "connection #" << conn_id << ": error_code = " << ec;
    socket.close();
}

