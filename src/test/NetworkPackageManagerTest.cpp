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
void NetworkPackageManagerTest::TestNetworkPackage::decode_payload(std::vector<unsigned char> command_data) {
    some_payload = command_data[0] << 24
                 | command_data[1] << 16
                 | command_data[2] << 8
                 | command_data[3] << 0;
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

void NetworkPackageManagerTest::encode_command_test()
{
    TestNetworkPackage test_command;
    test_command.some_payload = 0x12345678;
    auto vector = network_package_manager->encode_command(test_command);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0xEF, vector[0]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x00, vector[1]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x08, vector[2]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x12, vector[3]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x34, vector[4]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x56, vector[5]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x78, vector[6]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0xCD, vector[7]);
}

void NetworkPackageManagerTest::decode_command_test()
{
    const int payload = 0x12345678;
    TestNetworkPackage test_command;
    test_command.some_payload = payload;
    NetworkPackage& network_command = network_package_manager->decode_command(network_package_manager->encode_command(test_command));
    int decoded_payload = dynamic_cast<TestNetworkPackage*>(&network_command)->some_payload;
    CPPUNIT_ASSERT_EQUAL(payload, decoded_payload);
}


