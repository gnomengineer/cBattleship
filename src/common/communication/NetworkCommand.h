#ifndef _NETWORKCOMMAND_H
#define _NETWORKCOMMAND_H

#include <vector>

typedef unsigned char command_nr_t;

class NetworkCommand {
    public:
        virtual command_nr_t get_command_nr() = 0;
        virtual std::vector<unsigned char> encode_payload() = 0;
        virtual void decode_payload(std::vector<unsigned char> command_data) = 0;
};

#endif
