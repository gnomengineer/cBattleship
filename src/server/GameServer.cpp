#include "GameServer.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

GameServer::GameServer()
    : current_state(CHECK_FOR_CONNECTIONS), server() {

    std::cout << "BattleShipServer listening on 0.0.0.0:13477 ..." << std::endl;
}

GameServer::~GameServer() {
}

typedef GameServerState (GameServer::* GameServerFunc)(void);
typedef std::map<GameServerState, GameServerFunc> GameStateFuncMap;

void GameServer::run() {
    GameStateFuncMap state_func_map;
    state_func_map.insert(std::make_pair(CHECK_FOR_CONNECTIONS, &GameServer::check_for_connections_state));

    while(state_func_map.find(current_state) != state_func_map.end()) {
        auto function_ptr = state_func_map[current_state];
       current_state = (this->*function_ptr)();
       boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

GameServerState GameServer::check_for_connections_state() {
    int num_connections = server.get_connections().size();
    std::cout << "Connections: " << num_connections << std::endl;
    if(num_connections >= 2) {
        return STOP;
    }
    return CHECK_FOR_CONNECTIONS;
};


