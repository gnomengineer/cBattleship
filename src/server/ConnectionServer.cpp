#include "ConnectionServer.h"
#include <boost/thread/thread.hpp> 

ConnectionServer::ConnectionServer()
    : socket(io_service),
      endpoint(asio::ip::tcp::v4(), 13477),
      acceptor(io_service, endpoint),
      conn_id_gen(0) {
    accept_connections();

    boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
}

void ConnectionServer::accept_connections() {
    acceptor.async_accept(socket, [this](const boost::system::error_code& err_code) {
        if(!err_code) {
            connections.push_back(std::unique_ptr<Connection>(new Connection(conn_id_gen++, std::move(socket))));
        }
        accept_connections();
    });
}

std::list<std::unique_ptr<Connection>>& ConnectionServer::get_connections() {
    connections.remove_if([](const std::unique_ptr<Connection> & e) {
        auto & connection = *e;
        bool b = connection.is_connected();
        return !b;
    });
    return connections;
}

void ConnectionServer::handle_io() {
    io_service.run();
};
