#include "ConnectionServer.h"
#include <boost/thread/thread.hpp> 

ConnectionServer::ConnectionServer(NewConnectionHandler handler, std::string address, unsigned short port)
    : socket(io_service),
      endpoint(asio::ip::address().from_string(address), port),
      acceptor(io_service, endpoint),
      conn_id_gen(0),
      handler(handler) {
    accept_connections();

    boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
}

ConnectionServer::~ConnectionServer() {
    socket.close();
}

void ConnectionServer::accept_connections() {
    acceptor.async_accept(socket, [this](const boost::system::error_code& err_code) {
        if(!err_code) {
            handler(new Connection(conn_id_gen++, std::move(socket)));
        }
        accept_connections();
    });
}

void ConnectionServer::run() {
    io_service.run();
}
