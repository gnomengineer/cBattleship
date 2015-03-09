#include "GameServer.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <algorithm>

GameServer::GameServer()
    : state_machine(CHECK_FOR_CONNECTIONS, *this), server() {
    std::cout << "BattleShipServer listening on 0.0.0.0:13477 ..." << std::endl;
}

GameServer::~GameServer() {
}

GameServer::StateMachineType::StateMap GameServer::get_state_map() {
    StateMachineType::StateMap map;
    map[CHECK_FOR_CONNECTIONS] =  &GameServer::check_for_connections;
    map[SETUP_GAME] = &GameServer::setup_game;
    map[TURN_WAIT] = &GameServer::turn_wait;
    return map;
}

PlayerNetworkPackage GameServer::get_input() {
    while(input_queue.empty()) {
        auto & connections = server.get_connections();
        for(auto it = players.begin(); it != players.end(); it++) {
            conn_id_t id = it->first;
            bool still_connected = std::any_of(connections.begin(), connections.end(), [id](std::unique_ptr<Connection> & connection) {
                return connection->get_id() == id;
            });
            if(!still_connected) {
                players.erase(id);
            }
        }
        for(auto it = connections.begin(); it != connections.end(); it++) {
            auto& connection = **it;
            handle_connection(connection);
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(500));
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
            connection.disconnect();
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

void GameServer::register_new_connection(Connection & connection) {
    players[connection.get_id()] = std::unique_ptr<Player>(new Player(connection));
}

void GameServer::run() {
    state_machine.run();
}

void GameServer::next_player() {
    if(current_player != players_playing.end()) {
        current_player++;
    }
    if(current_player == players_playing.end()) {
        current_player = players_playing.begin();
    }
}

Player& GameServer::get_enemy() {
    auto current = current_player;
    next_player();
    auto enemy = current_player;
    current_player = current;
    return **enemy;
}

void GameServer::request_turn() {
    next_player();
    TurnRequestPackage turn_request_package;
    (*current_player)->get_connection().write(turn_request_package);
}


GameServerState GameServer::check_for_connections(PlayerNetworkPackage player_package) {
    Player& player = player_package.get_player();
    NetworkPackage& package = player_package.get_package();

    if(is_package_of_type<PlayerJoinPackage>(package)) {
        std::cout << "PlayerJoinPackage received" << std::endl;
        PlayerJoinPackage & p = cast_package<PlayerJoinPackage>(package);
        player.set_name(p.get_player_name());
        PlayerJoinAnswerPackage answer;

        auto randchar = []() -> char {
            const char charset[] = "abcdefghijklmnopqrstuvwxyz";
            const size_t size = sizeof(charset) - 1;
            return charset[rand() % size];
        };
        std::string identity(12, 0);
        std::generate_n(identity.begin(), 12, randchar);
        answer.set_identity(identity);
        player.get_connection().write(answer);
        players_playing.push_back(&player);
    }

    return players_playing.size() == 2 ? SETUP_GAME : CHECK_FOR_CONNECTIONS;
}

GameServerState GameServer::setup_game(PlayerNetworkPackage player_package) {
    Player& player = player_package.get_player();
    NetworkPackage& package = player_package.get_package();

    if(is_package_of_type<PlayerReadyPackage>(package)) {
        player.set_ready_to_start(true);
    }

    bool players_are_ready_to_start = std::all_of(players_playing.begin(), players_playing.end(), [](Player *player) {
        return player->is_ready_to_start();
    });
    
    if(players_are_ready_to_start) {
        request_turn();
        return TURN_WAIT;
    }
    return SETUP_GAME;
}

GameServerState GameServer::turn_wait(PlayerNetworkPackage player_package) {
    Player& player = player_package.get_player();
    NetworkPackage& package = player_package.get_package();

    if(is_package_of_type<TurnPackage>(package)) {
        if(&player == *current_player) {
            TurnPackage & p = cast_package<TurnPackage>(package);
            get_enemy().get_battle_field().hit_field(position(p.get_pos_x(), p.get_pos_y()));
            request_turn();
        }
    }
    return TURN_WAIT;
}
