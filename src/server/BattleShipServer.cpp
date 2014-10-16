#include "BattleShipServer.h"

BattleShipServer::BattleShipServer()
    : socket(io_service),
      endpoint(asio::ip::tcp::v4(), 13477),
      acceptor(io_service, endpoint) {
    accept_connections();
}

void BattleShipServer::accept_connections() {
    acceptor.async_accept(socket, [this](const boost::system::error_code& err_code) {
        if(!err_code) {
            connections.push_back(std::unique_ptr<Connection>(new Connection(std::move(socket))));
        }
        accept_connections();
    });
}
