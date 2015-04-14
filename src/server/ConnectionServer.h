#ifndef _BATTLESHIPSERVER_H
#define _BATTLESHIPSERVER_H

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>

#include <list>
#include <memory>

#include <common/Connection.h>

namespace asio = boost::asio;
typedef std::function<void(Connection*)> NewConnectionHandler;

class ConnectionServer {
    private:
        asio::io_service io_service;
        asio::ip::tcp::socket socket;
        asio::ip::tcp::endpoint endpoint;
        asio::ip::tcp::acceptor acceptor;

        conn_id_t conn_id_gen;

        NewConnectionHandler handler;

    public:
        ConnectionServer(NewConnectionHandler handler);
        ~ConnectionServer();
        void run();

    private:
        void accept_connections();
};
#endif
