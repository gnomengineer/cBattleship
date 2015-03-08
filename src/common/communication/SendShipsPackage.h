#ifndef _SENDSHIPSPACKAGE_H
#define _SENDSHIPSPACKAGE_H

#include <vector>
#include <common/position.h>

#include "NetworkPackage.h"
class SendShipsPackage : public NetworkPackage {
    private:
        std::vector<std::pair<unsigned int, orientation_t>> ships;


    public:
        SendShipsPackage();
        ~SendShipsPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        std::vector<std::pair<unsigned int, orientation_t>> get_ships();
        void set_ships(std::vector<std::pair<unsigned int, orientation_t>> ships);

};
#endif /* _SENDSHIPSPACKAGE_H */
