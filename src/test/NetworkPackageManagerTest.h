#ifndef _NETWORKPACKAGEMANAGERTEST_H
#define _NETWORKPACKAGEMANAGERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <common/NetworkPackageManager.h>
#include <packages.pb.h>


class NetworkPackageManagerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(NetworkPackageManagerTest);

    CPPUNIT_TEST(encode_package_test);
    CPPUNIT_TEST(decode_package_test);

    CPPUNIT_TEST_SUITE_END();

    private:
        class TestNetworkPackage : public GameReadyPackage {
        };
        NetworkPackageManager *network_package_manager;
      
    public:
        void setUp();
        void tearDown();
          
        void encode_package_test();
        void decode_package_test();

};

#endif  // NETWORKPACKAGEMANAGERTEST_H
