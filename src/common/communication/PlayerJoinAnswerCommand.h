#ifndef _PLAYERJOINANSWERCOMMAND_H
#define _PLAYERJOINANSWERCOMMAND_H

#include <string>
#include <vector>

#include "NetworkCommand.h"
class PlayerJoinAnswerCommand : public NetworkCommand {
    private:
        bool accepted;
        std::string identity;

    public:
        virtual command_nr_t get_command_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::string get_identity();
        void set_identity(std::string identity);
        void set_accepted(bool accepted);
        bool get_accepted();
};
#endif 
