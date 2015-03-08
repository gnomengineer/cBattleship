#ifndef _TURNREQUESTPACKAGE_H
#define _TURNREQUESTPACKAGE_H

#include <common/BattleField.h>

#include <vector>

#include "NetworkPackage.h"
class TurnRequestPackage : public NetworkPackage {
    private:
        BattleField your_battlefield;
        BattleField enemy_battlefield;


    public:
        TurnRequestPackage();
        ~TurnRequestPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> command_data);

        BattleField get_your_battlefield();
        void set_your_battlefield(BattleField your_battlefield);
        BattleField get_enemy_battlefield();
        void set_enemy_battlefield(BattleField enemy_battlefield);

};
#endif /* _TURNREQUESTPACKAGE_H */
