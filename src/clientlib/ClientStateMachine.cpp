#include "ClientStateMachine.h"
#include <boost/lexical_cast.hpp>
#include <common/Connection.h>
#include <common/Field.h>
#include <common/BattleField.h>
#include <packages.pb.h>

ClientStateMachine::ClientStateMachine(std::string host, unsigned int port)
    : io_service(), resolver(io_service), query(host, boost::lexical_cast<std::string>(port)),
      state_machine(INITIALIZE, *this),
      last_turn_position() {
    events.connecting(host, port);
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, resolver.resolve(query));
    connection = std::unique_ptr<Connection>(new Connection(1, std::move(socket)));
    events.connected();
}

ClientStateMachine::~ClientStateMachine() {
}

ClientStateMachine::StateMachineType::StateMap ClientStateMachine::get_state_map() {
    StateMachineType::StateMap map;
    map[INITIALIZE] = &ClientStateMachine::initialize;
    map[WAIT_FOR_JOIN] = &ClientStateMachine::wait_for_join;
    map[WAIT_FOR_GAME_START] = &ClientStateMachine::wait_for_game_start;
    map[YOUR_TURN] = &ClientStateMachine::your_turn;
    return map;
}

void ClientStateMachine::run() {
    static std::function<void(void)> get_input;
    get_input = [this]() -> void {
        connection->read([this](std::shared_ptr<NetworkPackage> package) {
            state_machine.run_state(*package);
            get_input();
        });
    };
    get_input();

    io_service.run();
}

void ClientStateMachine::stop() {
    io_service.stop();
}

void ClientStateMachine::get_turn() {
    events.get_turn(you, enemy, last_turn_position);
    TurnPackage turn;
    turn.set_identity(you.get_identity());
    turn.set_allocated_position(new Position(last_turn_position.as_package()));
    connection->write(turn);
    events.turn_confirmation_wait();
}

ClientState ClientStateMachine::initialize(NetworkPackage &package) {
    if(NetworkPackageManager::handle_package<GameConfigurationPackage>(package, [&](GameConfigurationPackage &gameConfig) {
        GameConfiguration config(gameConfig);
        you.create_battle_field(config.get_size_y(), config.get_size_x());
        enemy.create_battle_field(config.get_size_y(), config.get_size_x());
        events.get_game_configuration(config);

        std::string name;
        events.get_player_name(name);
        you.set_name(name);
        PlayerJoinPackage player_join_package;
        player_join_package.set_player_name(name);
        connection->write(player_join_package);

    })) return WAIT_FOR_JOIN;
    return INITIALIZE;
}

ClientState ClientStateMachine::wait_for_join(NetworkPackage &package) {
    if(NetworkPackageManager::handle_package<PlayerJoinAnswerPackage>(package, [&](PlayerJoinAnswerPackage &package) {
        events.new_identity(package.identity());
        you.set_identity(package.identity());
    })) return WAIT_FOR_GAME_START;
    return WAIT_FOR_JOIN;
}

ClientState ClientStateMachine::wait_for_game_start(NetworkPackage &package) {
    ClientState state = WAIT_FOR_GAME_START;

    NetworkPackageManager::handle_package<GameReadyPackage>(package, [&](GameReadyPackage &game_ready_package) {
        enemy.set_name(game_ready_package.enemy_name());

        events.place_ships(you);
        ShipPlacementPackage ship_placement_package;
        ship_placement_package.set_identity(you.get_identity());
        std::vector<ShipData> ship_data = you.get_battle_field().get_ship_data();
        std::for_each(ship_data.begin(), ship_data.end(), [&](ShipData ship) {
            ship.Swap(ship_placement_package.add_ship_data());
        });
        connection->write(ship_placement_package);
        events.place_ship_confirmation_wait();
    });

    NetworkPackageManager::handle_package<ShipPlacementResponsePackage>(package, [&](ShipPlacementResponsePackage &response) {
        if(response.valid()) {
            events.place_ship_ok();
            state = YOUR_TURN;
        } else {
            events.place_ship_error(
                response.out_of_bounds(),
                response.ships_overlap(),
                response.remaining_ships()
            );

            you.get_battle_field().clear();
            events.place_ships(you);
            ShipPlacementPackage ship_placement_package;
            ship_placement_package.set_identity(you.get_identity());
            auto ship_data_vector = you.get_battle_field().get_ship_data();
            std::for_each(ship_data_vector.begin(), ship_data_vector.end(), [&](ShipData ship) {
                ship.Swap(ship_placement_package.add_ship_data());
            });
            connection->write(ship_placement_package);
            events.place_ship_confirmation_wait();
        }
    });
    return state;
}

ClientState ClientStateMachine::your_turn(NetworkPackage &package) {
    NetworkPackageManager::handle_package<EnemyHitPackage>(package, [&](EnemyHitPackage &enemy_hit_package) {
        you.get_battle_field().hit_field(position(enemy_hit_package.position()));
        events.enemy_hit(enemy_hit_package.enemy_hit(), position(enemy_hit_package.position()));
    });

    NetworkPackageManager::handle_package<TurnRequestPackage>(package, [&](TurnRequestPackage &package) {
        get_turn();
    });

    NetworkPackageManager::handle_package<TurnResponsePackage>(package, [&](TurnResponsePackage &turn_response) {
        if(!turn_response.valid()) {
            events.turn_error();
            get_turn();
        } else {
            auto field = enemy.get_battle_field().get_field(last_turn_position);

            field->set_ship_part(turn_response.ship_hit());
            field->set_hit();
            events.turn_ok(turn_response.ship_hit(), turn_response.ship_of_length_destroyed());
            events.enemy_wait();
        }
    });

    if(NetworkPackageManager::handle_package<EnemyDisconnectedPackage>(package, [&](EnemyDisconnectedPackage &package) {
        events.enemy_disconnected();
    })) return STOP;

    if(NetworkPackageManager::handle_package<GameEndedPackage>(package, [&](GameEndedPackage &end_package) {
        auto ship_data = end_package.enemy_ships();
        std::vector<ShipData> vector_ship_data(ship_data.begin(), ship_data.end());
        enemy.get_battle_field().add_ship_data(vector_ship_data);
        events.game_ended(end_package.won(), you, enemy);
    })) return STOP;
    return YOUR_TURN;
}
