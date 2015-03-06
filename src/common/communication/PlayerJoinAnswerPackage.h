#ifndef _PLAYERJOINANSWERPACKAGE_H
#define _PLAYERJOINANSWERPACKAGE_H

#include <string>
#include <vector>

#include "NetworkPackage.h"
class PlayerJoinAnswerPackage : public NetworkPackage {
    private:
        std::string identity;

    public:
        PlayerJoinAnswerPackage();
        ~PlayerJoinAnswerPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::string get_identity();
        void set_identity(std::string identity);
};
#endif 
