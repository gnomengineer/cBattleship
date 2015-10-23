#include "Bot.h"
#include "Process.h"

#include <common/GameConfiguration.h>
#include <common/BattleField.h>
#include <clientlib/Player.h>
#include <sstream>
#include <algorithm>

Bot::Bot(std::string bot_executable)
    : executable(bot_executable) {
}

Bot::~Bot() {
}

Process *Bot::make_process(std::string calltype) {
    std::vector<std::string> arguments;
    arguments.push_back(calltype);
    return new Process(executable, arguments);
}

std::string Bot::get_bot_name() {
    std::unique_ptr<Process> process(make_process("name"));
    return process->read();
}

std::vector<ShipData> Bot::make_ship_placement(GameConfiguration &config) {
    std::unique_ptr<Process> process(make_process("ships"));
    send_rules(*process, config);
    // TODO: parse bot input
}

position_t Bot::make_turn(Player &you, Player &enemy, GameConfiguration &config) {
    std::unique_ptr<Process> process(make_process("turn"));
    send_rules(*process, config);
    send_own_battle_field(*process, you.get_battle_field());
    send_enemy_battle_field(*process, you.get_battle_field());
    // TODO: parse bot input
}

void Bot::send_rules(Process &process, GameConfiguration &config) {
    std::stringstream ss;
    ss << "h ";
    ss << (config.get_hitspree() ? 1 : 0);
    ss << "\n";
    process.write(ss.str());

    send_battle_field_size(process, config);
    send_ships_available(process, config);
}

void Bot::send_battle_field_size(Process &process, GameConfiguration &config) {
    std::stringstream ss;
    ss << "b ";
    ss << config.get_size_y();
    ss << " ";
    ss << config.get_size_x();
    ss << "\n";
    process.write(ss.str());
}

void Bot::send_ships_available(Process &process, GameConfiguration &config) {
    std::stringstream ss;
    auto ships_available = config.get_ships_available();
    std::for_each(ships_available.begin(), ships_available.end(), [&ss](std::pair<unsigned int, unsigned int> p) {
        ss << "s " << p.first << " " << p.second << "\n";
    });
    process.write(ss.str());
}

void Bot::send_own_battle_field(Process &process, BattleField &your_battle_field) {
    send_battle_field(process, your_battle_field, "y");
}

void Bot::send_enemy_battle_field(Process &process, BattleField &your_battle_field) {
    send_battle_field(process, your_battle_field, "e");
}

void Bot::send_battle_field(Process &process, BattleField &battle_field, std::string type) {
    std::stringstream ss;
    auto fields = battle_field.to_vector();
    std::for_each(fields.begin(), fields.end(), [&ss, type](std::vector<unsigned char> row) {
        ss << type;
        std::for_each(row.begin(), row.end(), [&ss](unsigned char field) {
            ss << " " << field;
        });
        ss << "\n";
    });
    process.write(ss.str());
}
