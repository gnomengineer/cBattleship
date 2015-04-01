#include "NetworkPackageManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NetworkPackageManagerTest);

package_nr_t NetworkPackageManagerTest::TestNetworkPackage::get_package_nr() {
    return 0xEF;
}

std::vector<unsigned char> NetworkPackageManagerTest::TestNetworkPackage::encode_payload() {
    std::vector<unsigned char> payload(4);
    payload[0] = (some_payload >> 24) & 0xFF;
    payload[1] = (some_payload >> 16) & 0xFF;
    payload[2] = (some_payload >>  8) & 0xFF;
    payload[3] = (some_payload >>  0) & 0xFF;
    return payload;
}
void NetworkPackageManagerTest::TestNetworkPackage::decode_payload(std::vector<unsigned char> package_data) {
    some_payload = package_data[0] << 24
                 | package_data[1] << 16
                 | package_data[2] << 8
                 | package_data[3] << 0;
}

void NetworkPackageManagerTest::setUp()
{
    network_package_manager = new NetworkPackageManager();
    // doesn't need to be added everytime, is just overwritten
    network_package_manager->add_network_commands<TestNetworkPackage>();
}


void NetworkPackageManagerTest::tearDown()
{
    delete network_package_manager;
}

void NetworkPackageManagerTest::encode_package_test()
{
    TestNetworkPackage test_command;
    test_command.some_payload = 0x12345678;
    auto vector = network_package_manager->encode_package(test_command);
    CPPUNIT_ASSERT_EQUAL((int)0xEF, (int)vector[0]);
    CPPUNIT_ASSERT_EQUAL((int)0x08, (int)vector[1]);
    CPPUNIT_ASSERT_EQUAL((int)0x00, (int)vector[2]);
    CPPUNIT_ASSERT_EQUAL((int)0x12, (int)vector[3]);
    CPPUNIT_ASSERT_EQUAL((int)0x34, (int)vector[4]);
    CPPUNIT_ASSERT_EQUAL((int)0x56, (int)vector[5]);
    CPPUNIT_ASSERT_EQUAL((int)0x78, (int)vector[6]);
    CPPUNIT_ASSERT_EQUAL((int)0xCD, (int)vector[7]);
}

void NetworkPackageManagerTest::decode_package_test()
{
    const int payload = 0x12345678;
    TestNetworkPackage test_command;
    test_command.some_payload = payload;
    NetworkPackage& network_command = network_package_manager->decode_package(network_package_manager->encode_package(test_command));
    int decoded_payload = dynamic_cast<TestNetworkPackage*>(&network_command)->some_payload;
    CPPUNIT_ASSERT_EQUAL(payload, decoded_payload);
}


