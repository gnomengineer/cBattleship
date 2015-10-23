#ifndef _BOTCLIENT_H
#define _BOTCLIENT_H

#include <memory>
#include <common/position.h>
#include <string>

class ClientStateMachine;
class Bot;
class Player;
class BattleField;
class GameConfiguration;

class BotClient {
    private:
        position_t last_turn_position;
        std::unique_ptr<ClientStateMachine> client_state_machine;
        std::unique_ptr<Bot> bot;
        std::unique_ptr<GameConfiguration> config;

    public:
        BotClient(std::string host, unsigned int port, std::string bot);
        virtual ~BotClient();
        void run();
};


#endif
