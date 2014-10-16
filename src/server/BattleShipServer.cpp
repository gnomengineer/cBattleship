#include "BattleShipServer.h"
#include <boost/thread/thread.hpp> 

BattleShipServer::BattleShipServer()
    : socket(io_service),
      endpoint(asio::ip::tcp::v4(), 13477),
      acceptor(io_service, endpoint) {
    accept_connections();

    boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));
}

void BattleShipServer::accept_connections() {
    acceptor.async_accept(socket, [this](const boost::system::error_code& err_code) {
        if(!err_code) {
            connections.push_back(std::unique_ptr<Connection>(new Connection(std::move(socket))));
        }
        accept_connections();
    });
}

std::list<std::unique_ptr<Connection>>& BattleShipServer::get_connections() {
    return connections;
}

void BattleShipServer::handle_io() {
    io_service.run();
};
