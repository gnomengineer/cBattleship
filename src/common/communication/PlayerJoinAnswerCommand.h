#ifndef _PLAYERJOINANSWERCOMMAND_H
#define _PLAYERJOINANSWERCOMMAND_H

#include <string>
#include <vector>

#include "NetworkPackage.h"
class PlayerJoinAnswerCommand : public NetworkPackage {
    private:
        bool accepted;
        std::string identity;

    public:
        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::string get_identity();
        void set_identity(std::string identity);
        void set_accepted(bool accepted);
        bool get_accepted();
};
#endif 
