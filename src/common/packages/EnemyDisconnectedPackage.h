#ifndef _ENEMYDISCONNECTEDPACKAGE_H
#define _ENEMYDISCONNECTEDPACKAGE_H

#include <vector>

#include "NetworkPackage.h"
class EnemyDisconnectedPackage : public NetworkPackage {
    private:

    public:
        EnemyDisconnectedPackage();
        virtual ~EnemyDisconnectedPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

};
#endif /* _ENEMYDISCONNECTEDPACKAGE_H */
