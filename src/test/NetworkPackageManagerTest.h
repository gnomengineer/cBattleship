#ifndef _NETWORKPACKAGEMANAGERTEST_H
#define _NETWORKPACKAGEMANAGERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <common/NetworkPackageManager.h>
#include <packages.pb.h>


class NetworkPackageManagerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(NetworkPackageManagerTest);

    CPPUNIT_TEST(encode_package_test);
    CPPUNIT_TEST(decode_package_nr_test);
    CPPUNIT_TEST(decode_inner_package_test);

    CPPUNIT_TEST_SUITE_END();

    private:
        class TestNetworkPackage : public PlayerJoinPackage {
        };
        NetworkPackageManager *network_package_manager;

        std::vector<unsigned char> encoded;

        NetworkPackage network_package;
      
    public:
        void setUp();
        void tearDown();
          
        void encode_package_test();
        void decode_package_nr_test();
        void decode_inner_package_test();

};

#endif  // NETWORKPACKAGEMANAGERTEST_H
