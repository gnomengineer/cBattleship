#include "SimpleClient.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <algorithm>

SimpleClient::SimpleClient(Connection &connection)
    : state_machine(GET_IDENTITY, *this),  connection(connection) {
}

SimpleClient::~SimpleClient() {
}

SimpleClient::StateMachineType::StateMap SimpleClient::get_state_map() {
    StateMachineType::StateMap map;
    map[GET_IDENTITY] = &SimpleClient::get_identity;
    map[WAIT_FOR_GAME_START] = &SimpleClient::wait_for_game_start;
    return map;
}

std::string SimpleClient::ask_user(std::string prompt, std::string default_value) {
    std::string value;
    std::cout << prompt << std::flush;
    std::cin >> value;
    if(!std::cin.good()) value = default_value;
    return value;
}

void SimpleClient::run() {
    std::string name = ask_user("your nickname: ", "unnamed");
    PlayerJoinPackage player_join_package;
    player_join_package.set_player_name(name);
    connection.write(player_join_package);

    static std::function<void(void)> get_input;
    get_input = [this]() -> void {
        connection.read([this](NetworkPackage& command) {
            ServerNetworkPackage package(command);
            state_machine.run_state(package);
            get_input();
        });
    };
    get_input();
}


SimpleClientState SimpleClient::get_identity(ServerNetworkPackage server_package) {
    std::cout << "get identity" << std::endl;
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<PlayerJoinAnswerPackage>(package)) {
         PlayerJoinAnswerPackage & answer = cast_package<PlayerJoinAnswerPackage>(package);
         you.set_identity(answer.get_identity());
         std::cout << "identity: " << you.get_identity() << std::endl;
         ShipPlacementPackage ship_placement_package;
         ship_placement_package.set_identity(answer.get_identity());
         connection.write(ship_placement_package);
        return WAIT_FOR_GAME_START;
    }
    return GET_IDENTITY;
}

SimpleClientState SimpleClient::wait_for_game_start(ServerNetworkPackage server_package) {
    std::cout << "waiting for game to start ... " << std::endl;
    return STOP;
}
