#include "BotClient.h"
#include "Bot.h"
#include <iostream>
#include <iomanip>
#include <clientlib/ClientStateMachine.h>
#include <common/BattleField.h>
#include <common/GameConfiguration.h>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <memory>

BotClient::BotClient(std::string host, unsigned int port, std::string bot)
    : client_state_machine(new ClientStateMachine(host, port)),
      bot(new Bot(bot)) {
    client_state_machine->events.connecting.connect([](std::string host, unsigned int port) {
        BOOST_LOG_TRIVIAL(info) << "trying to connect to '" << host << ":" << port << "' ... ";
    });

    client_state_machine->events.connected.connect([]() {
        BOOST_LOG_TRIVIAL(info) << "trying to join server... ";
    });

    client_state_machine->events.get_game_configuration.connect([this](GameConfiguration config) {
        BOOST_LOG_TRIVIAL(info) << "board: " << config.get_size_x() << "|" << config.get_size_y() << ", hitspree: " << config.get_hitspree();
        this->config = std::unique_ptr<GameConfiguration>(new GameConfiguration(config));
    });

    client_state_machine->events.get_player_name.connect([this](std::string &name) {
        name = this->bot->get_bot_name();
    });

    client_state_machine->events.new_identity.connect([](std::string identity) {
    });

    client_state_machine->events.place_ships.connect([this](Player &you) {
        BOOST_LOG_TRIVIAL(info) << "asking bot for ship placement";
        this->bot->make_ship_placement(*this->config);
        // TODO: apply vector of ship data to battlefield
    });

    client_state_machine->events.place_ship_ok.connect([]() {
        BOOST_LOG_TRIVIAL(info) << "placement confirmed by server";
    });

    client_state_machine->events.place_ship_confirmation_wait.connect([]() {
        BOOST_LOG_TRIVIAL(info) << "waiting for confirmation of ship placement";
    });

    client_state_machine->events.place_ship_error.connect([](bool out_of_bounds, bool overlap, int remaining_ships) {
        // TODO:: handle invalid ship placement of bot
    });

    client_state_machine->events.get_turn.connect([this](Player &you, Player &enemy, position_t &position) {
        BOOST_LOG_TRIVIAL(info) << "asking bot for ship placement";
        position = this->bot->make_turn(you, enemy, *this->config);
    });

    client_state_machine->events.turn_confirmation_wait.connect([]() {
        BOOST_LOG_TRIVIAL(info) << "waiting for turn confirmation";
    });

    client_state_machine->events.turn_ok.connect([this](bool did_you_hit, int ship_of_length_destroyed) {
        // TODO: send info to bot wheter hit was successful
    });

    client_state_machine->events.turn_error.connect([]() {
        // TODO: handle invalid turn of bot
    });

    client_state_machine->events.enemy_hit.connect([](bool hit, position_t position) {
        // TODO: send info of enemy hit to bot
    });


    client_state_machine->events.enemy_wait.connect([]() {
    });

    client_state_machine->events.enemy_disconnected.connect([]() {
    });

    client_state_machine->events.game_ended.connect([this](bool won, Player &you, Player &enemy) {
    });

}

BotClient::~BotClient() {
}

void BotClient::run() {
    client_state_machine->run();
}
