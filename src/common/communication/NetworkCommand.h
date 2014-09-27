#ifndef _NETWORKCOMMAND_H
#define _NETWORKCOMMAND_H

#include <vector>

class NetworkCommand {
    public:
        virtual std::vector<unsigned char> encode_payload() = 0;
        virtual void dencode_payload(std::vector<unsigned char> command_data) = 0;
};

#endif
