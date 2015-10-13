#ifndef GAMESERVERUTIL_H
#define GAMESERVERUTIL_H

#include <string.h>
#include "Player.h"

class GameServerUtil {
    public:
        static std::string generate_identity() {
            auto randchar = []() -> char {
                const char charset[] = "abcdefghijklmnopqrstuvwxyz";
                const size_t size = sizeof(charset) - 1;
                return charset[rand() % size];
            };
            std::string identity(IDENTITY_LENGTH, 0);
            std::generate_n(identity.begin(), IDENTITY_LENGTH, randchar);
            return identity;
        }

        static bool players_ready_to_start(std::list<Player*> players_playing) {
            return std::all_of(players_playing.begin(), players_playing.end(), [](Player *player) {
                return player->is_ready_to_start();
            });
        }

};

#endif /* GAMESERVERUTIL_H */
