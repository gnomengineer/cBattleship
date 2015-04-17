#ifndef _NETWORKPACKAGEMANAGERTEST_H
#define _NETWORKPACKAGEMANAGERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <common/packages/NetworkPackage.h>
#include <common/packages/NetworkPackageManager.h>

class NetworkPackageManagerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(NetworkPackageManagerTest);

    CPPUNIT_TEST(encode_package_test);
    CPPUNIT_TEST(decode_package_test);

    CPPUNIT_TEST_SUITE_END();

    private:
        class TestNetworkPackage : public NetworkPackage {
            public:
                int some_payload;
                virtual package_nr_t get_package_nr();
                virtual std::vector<unsigned char> encode_payload();
                virtual void decode_payload(std::vector<unsigned char> package_data);
        };
        NetworkPackageManager *network_package_manager;
      
    public:
        void setUp();
        void tearDown();
          
        void encode_package_test();
        void decode_package_test();

};

#endif  // NETWORKPACKAGEMANAGERTEST_H
