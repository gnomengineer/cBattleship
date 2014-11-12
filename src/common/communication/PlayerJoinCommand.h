#ifndef _PLAYERJOINCOMMAND_H
#define _PLAYERJOINCOMMAND_H

#include <string>
#include <vector>

#include "NetworkCommand.h"
class PlayerJoinCommand : public NetworkCommand {
    private:
        std::string player_name;

    public:
        virtual command_nr_t get_command_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::string get_player_name();
        void set_player_name(std::string player_name);
};
#endif 
