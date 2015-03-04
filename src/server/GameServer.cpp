#include "GameServer.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

GameServer::GameServer()
    : state_machine(CHECK_FOR_CONNECTIONS, *this), server() {
    std::cout << "BattleShipServer listening on 0.0.0.0:13477 ..." << std::endl;
}

GameServer::~GameServer() {
}

GameServer::StateMachineType::StateMap GameServer::get_state_map() {
    StateMachineType::StateMap map;
    map[CHECK_FOR_CONNECTIONS] =  &GameServer::check_for_connections;
    return map;
}

PlayerNetworkPackage GameServer::get_input() {
    while(input_queue.empty()) {
        auto& connections = server.get_connections();
        for(auto it = connections.begin(); it != connections.end(); it++) {
            auto& connection = **it;
            handle_connection(connection);
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }

    std::lock_guard<std::mutex> lock(queue_lock);
    PlayerNetworkPackage player_command = input_queue.front();
    input_queue.pop();
    return player_command;
}

void GameServer::handle_connection(Connection & connection) {
    if(is_new_connection(connection)) {
        if(can_handle_new_connection()) {
            register_new_connection(connection);
        } else {
             // TODO: drop connection
        }
    } else {
        handle_player_connection(connection);
    }
}

void GameServer::handle_player_connection(Connection & connection) {
    auto & player = *players[connection.get_id()].get();
    connection.read([this, &player](NetworkPackage& command) {
        std::lock_guard<std::mutex> lock(queue_lock);
        std::cout << "received command #" << (int)command.get_package_nr() << " from client" << std::endl;
        PlayerNetworkPackage pcmd(command, player);
        input_queue.push(pcmd);
    });
}

bool GameServer::is_new_connection(Connection & connection) {
    return players.find(connection.get_id()) == players.end();
}

bool GameServer::can_handle_new_connection() {
    return players.size() < 2;
}

void GameServer::register_new_connection(Connection & conn) {
    players[conn.get_id()] = std::unique_ptr<Player>(new Player(conn.get_id()));
}

void GameServer::run() {
    state_machine.run();
}

GameServerState GameServer::check_for_connections(PlayerNetworkPackage command) {

    
    if(server.get_connections().size() >= 2) {
        return STOP;
    }
    return CHECK_FOR_CONNECTIONS;
};


