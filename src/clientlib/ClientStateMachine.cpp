#include "ClientStateMachine.h"

ClientStateMachine::ClientStateMachine(std::string connection_string)
    : io_service(), resolver(io_service), query(connection_string, "13477"),
      state_machine(GET_IDENTITY, *this),
      last_turn_position() {
    events.connecting(connection_string);
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, resolver.resolve(query));
    connection = std::unique_ptr<Connection>(new Connection(1, std::move(socket)));
    events.connected();
}

ClientStateMachine::~ClientStateMachine() {
}

ClientStateMachine::StateMachineType::StateMap ClientStateMachine::get_state_map() {
    StateMachineType::StateMap map;
    map[GET_IDENTITY] = &ClientStateMachine::get_identity;
    map[WAIT_FOR_GAME_START] = &ClientStateMachine::wait_for_game_start;
    map[YOUR_TURN] = &ClientStateMachine::your_turn;
    return map;
}

void ClientStateMachine::run() {
    std::string name;
    events.get_player_name(name);
    you.set_name(name);
    PlayerJoinPackage player_join_package;
    player_join_package.set_player_name(name);
    connection->write(player_join_package);

    static std::function<void(void)> get_input;
    get_input = [this]() -> void {
        connection->read([this](NetworkPackage& command) {
            ServerNetworkPackage package(command);
            state_machine.run_state(package);
            get_input();
        });
    };
    get_input();

    io_service.run();
}

void ClientStateMachine::get_turn() {
    events.get_turn(you, enemy, last_turn_position);
    TurnPackage turn;
    turn.set_identity(you.get_identity());
    turn.set_position(last_turn_position);
    connection->write(turn);
    events.turn_confirmation_wait();
}

ClientState ClientStateMachine::get_identity(ServerNetworkPackage server_package) {
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<PlayerJoinAnswerPackage>(package)) {
         PlayerJoinAnswerPackage & answer = cast_package<PlayerJoinAnswerPackage>(package);
         events.new_identity(answer.get_identity());
         you.set_identity(answer.get_identity());
        return WAIT_FOR_GAME_START;
    }
    return GET_IDENTITY;
}

ClientState ClientStateMachine::wait_for_game_start(ServerNetworkPackage server_package) {
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<GameReadyPackage>(package)) {
        GameReadyPackage & game_ready_package = cast_package<GameReadyPackage>(package);
        enemy.set_name(game_ready_package.get_enemy_name());

        events.place_ships(you);
        ShipPlacementPackage ship_placement_package;
        ship_placement_package.set_identity(you.get_identity());
        ship_placement_package.set_ship_data(you.get_battle_field().get_ship_data());
        connection->write(ship_placement_package);
        events.place_ship_confirmation_wait();
    } else if(is_package_of_type<ShipPlacementResponsePackage>(package)) {
        auto &response = cast_package<ShipPlacementResponsePackage>(package);
        if(response.get_valid()) {
            events.place_ship_ok();
            return YOUR_TURN;
        } else {
            events.place_ship_error(
                response.get_out_of_bounds(),
                response.get_ships_overlap(),
                response.get_remaining_ships()
            );

            you.get_battle_field().clear();
            events.place_ships(you);
            ShipPlacementPackage ship_placement_package;
            ship_placement_package.set_identity(you.get_identity());
            ship_placement_package.set_ship_data(you.get_battle_field().get_ship_data());
            connection->write(ship_placement_package);
            events.place_ship_confirmation_wait();
        }
    }
    return WAIT_FOR_GAME_START;
}

ClientState ClientStateMachine::your_turn(ServerNetworkPackage server_package) {
    NetworkPackage &package = server_package.get_package();
    if(is_package_of_type<TurnRequestPackage>(package)) {
        auto& turn_request = cast_package<TurnRequestPackage>(package);
        if(turn_request.get_enemy_hit()) {
            you.get_battle_field().hit_field(turn_request.get_position());
            events.enemy_hit(you, turn_request.get_position());
        }
        get_turn();
    } else if(is_package_of_type<TurnResponsePackage>(package)) {
        auto& turn_response = cast_package<TurnResponsePackage>(package);

        if(!turn_response.get_valid()) {
            events.turn_error();
            get_turn();
        } else {
            auto field = enemy.get_battle_field().get_field(last_turn_position);

            field->set_ship_part(turn_response.get_ship_hit());
            field->set_hit();
            events.turn_ok(turn_response.get_ship_hit(), turn_response.get_ship_of_length_destroyed());
            events.enemy_wait();
        }
    } else if(is_package_of_type<EnemyDisconnectedPackage>(package)) {
        events.enemy_disconnected();
        return STOP;

    } else if(is_package_of_type<GameEndedPackage>(package)) {
        auto& end_package = cast_package<GameEndedPackage>(package);
        auto ship_data = end_package.get_enemy_ships();
        enemy.get_battle_field().add_ship_data(ship_data);
        events.game_ended(end_package.get_won(), you, enemy);
        return STOP;
    }
    return YOUR_TURN;
}
