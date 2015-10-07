#ifndef _ENEMYHITPACKAGE_H
#define _ENEMYHITPACKAGE_H

#include <vector>
#include <common/position.h>

#include "NetworkPackage.h"
class EnemyHitPackage : public NetworkPackage {
    private:
        bool enemy_hit;
        position_t position;

    public:
        EnemyHitPackage();
        virtual ~EnemyHitPackage();

        virtual package_nr_t get_package_nr();
        virtual std::vector<unsigned char> encode_payload();
        virtual void decode_payload(std::vector<unsigned char> package_data);

        bool get_enemy_hit();
        void set_enemy_hit(bool enemy_hit);
        position_t get_position();
        void set_position(position_t position);
};
#endif /* _ENEMYHITPACKAGE_H */
