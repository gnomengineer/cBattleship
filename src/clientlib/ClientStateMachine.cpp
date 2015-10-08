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
        connection->read([this](NetworkPackage &package) {
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

ClientState ClientStateMachine::get_identity(NetworkPackage &package) {
    if(handle_package<PlayerJoinAnswerPackage>(package, [&](PlayerJoinAnswerPackage &package) {
        events.new_identity(package.get_identity());
        you.set_identity(package.get_identity());
    })) return WAIT_FOR_GAME_START;
    handle_package<GameConfigurationPackage>(package, [&](GameConfigurationPackage &gameConfig) {
        events.get_game_configuration(gameConfig.get_config());
    });
    return GET_IDENTITY;
}

ClientState ClientStateMachine::wait_for_game_start(NetworkPackage &package) {
    ClientState state = WAIT_FOR_GAME_START;

    handle_package<GameReadyPackage>(package, [&](GameReadyPackage &game_ready_package) {
        enemy.set_name(game_ready_package.get_enemy_name());

        events.place_ships(you);
        ShipPlacementPackage ship_placement_package;
        ship_placement_package.set_identity(you.get_identity());
        ship_placement_package.set_ship_data(you.get_battle_field().get_ship_data());
        connection->write(ship_placement_package);
        events.place_ship_confirmation_wait();
    });

    handle_package<ShipPlacementResponsePackage>(package, [&](ShipPlacementResponsePackage &response) {
        if(response.get_valid()) {
            events.place_ship_ok();
            state = YOUR_TURN;
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
    });
    return state;
}

ClientState ClientStateMachine::your_turn(NetworkPackage &package) {
    handle_package<EnemyHitPackage>(package, [&](EnemyHitPackage &enemy_hit_package) {
        if(enemy_hit_package.get_enemy_hit()) {
            you.get_battle_field().hit_field(enemy_hit_package.get_position());
        }
        events.enemy_hit(enemy_hit_package.get_enemy_hit(), enemy_hit_package.get_position());
    });

    handle_package<TurnRequestPackage>(package, [&](TurnRequestPackage &package) {
        get_turn();
    });

    handle_package<TurnResponsePackage>(package, [&](TurnResponsePackage &turn_response) {
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
    });

    if(handle_package<EnemyDisconnectedPackage>(package, [&](EnemyDisconnectedPackage &package) {
        events.enemy_disconnected();
    })) return STOP;

    if(handle_package<GameEndedPackage>(package, [&](GameEndedPackage &end_package) {
        auto ship_data = end_package.get_enemy_ships();
        enemy.get_battle_field().add_ship_data(ship_data);
        events.game_ended(end_package.get_won(), you, enemy);
    })) return STOP;
    return YOUR_TURN;
}
