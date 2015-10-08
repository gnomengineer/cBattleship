#include "NetworkPackageManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NetworkPackageManagerTest);

void NetworkPackageManagerTest::setUp()
{
    network_package_manager = new NetworkPackageManager();
    // doesn't need to be added everytime, is just overwritten
    network_package_manager->add_network_packages<TestNetworkPackage>();
}


void NetworkPackageManagerTest::tearDown()
{
    delete network_package_manager;
}

void NetworkPackageManagerTest::encode_package_test()
{
    TestNetworkPackage test_package;
    auto vector = network_package_manager->encode_package(test_package);
    CPPUNIT_ASSERT_EQUAL((int)0x08, (int)vector[1]);
    CPPUNIT_ASSERT_EQUAL((int)0x00, (int)vector[2]);
    CPPUNIT_ASSERT_EQUAL((int)0x01, (int)vector[0]);
    CPPUNIT_ASSERT_EQUAL((int)0xCD, (int)vector[vector.size() - 1]);
}

void NetworkPackageManagerTest::decode_package_test()
{
    CPPUNIT_FAIL("not implemented");
}


