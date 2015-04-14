#ifndef GAMESERVERUTIL_H
#define GAMESERVERUTIL_H

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
};

#endif /* GAMESERVERUTIL_H */
