#ifndef _PLAYERJOINANSWERPACKAGE_H
#define _PLAYERJOINANSWERPACKAGE_H

#include <string>
#include <vector>

#include "AuthenticatedNetworkPackage.h"
class PlayerJoinAnswerPackage : public AuthenticatedNetworkPackage {
    public:
        PlayerJoinAnswerPackage();
        virtual ~PlayerJoinAnswerPackage();

        virtual package_nr_t get_package_nr();
};
#endif 
