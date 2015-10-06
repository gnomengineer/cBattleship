#ifndef _PLAYERJOINANSWERPACKAGE_H
#define _PLAYERJOINANSWERPACKAGE_H

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include "NetworkPackage.h"

class PlayerJoinAnswerPackage : public NetworkPackage {
    private:
        /* this class is serializable through
           the boost.serialization library */
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<NetworkPackage>(*this);
            ar & this->identity;
        }

        std::string identity;

    public:
        PlayerJoinAnswerPackage() { }
        virtual ~PlayerJoinAnswerPackage() { }

        virtual package_nr_t get_package_nr() {
            return 0x21;
        }

        std::string get_identity() {
            return identity;
        }

        void set_identity(std::string identity) {
            this->identity = identity;
        }

};


#endif /* _PLAYERJOINANSWERPACKAGE_H */
