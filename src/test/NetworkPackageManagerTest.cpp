#include "NetworkPackageManagerTest.h"
#include <iostream>
#include <iomanip>

CPPUNIT_TEST_SUITE_REGISTRATION(NetworkPackageManagerTest);

void NetworkPackageManagerTest::setUp() {
    network_package_manager = new NetworkPackageManager();
    // doesn't need to be added everytime, is just overwritten
    network_package_manager->add_network_packages<TestNetworkPackage>();

    TestNetworkPackage test_package;
    std::string name = "chuck testa";
    test_package.set_player_name(name);
    encoded = network_package_manager->encode_package(test_package);

    network_package = network_package_manager->decode_package(encoded);
}


void NetworkPackageManagerTest::tearDown() {
    delete network_package_manager;
}

void NetworkPackageManagerTest::encode_package_test() {
    unsigned int length = encoded.size();
    CPPUNIT_ASSERT_EQUAL((int)(length & 255), (int)encoded[0]);
    CPPUNIT_ASSERT_EQUAL((int)((length >> 8) & 255), (int)encoded[1]);
    CPPUNIT_ASSERT_EQUAL((int)0xCD, (int)encoded[length - 1]);
}

void NetworkPackageManagerTest::decode_package_nr_test() {
    CPPUNIT_ASSERT_EQUAL(NetworkPackageManager::get_package_nr<TestNetworkPackage>(),
                         network_package.package_nr());
}

void NetworkPackageManagerTest::decode_inner_package_test() {
    bool ret = NetworkPackageManager::handle_package<TestNetworkPackage>(network_package,
        [](TestNetworkPackage & package) {
            CPPUNIT_ASSERT_EQUAL(std::string("chuck testa"), package.player_name());
        }
    );
    CPPUNIT_ASSERT(ret);
}


