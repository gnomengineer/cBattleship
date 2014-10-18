#include "NetworkInterfaceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NetworkInterfaceTest);

command_nr_t NetworkInterfaceTest::TestNetworkCommand::get_command_nr() {
    return 0xEF;
}

std::vector<unsigned char> NetworkInterfaceTest::TestNetworkCommand::encode_payload() {
    std::vector<unsigned char> payload(4);
    payload[0] = (some_payload >> 24) & 0xFF;
    payload[1] = (some_payload >> 16) & 0xFF;
    payload[2] = (some_payload >>  8) & 0xFF;
    payload[3] = (some_payload >>  0) & 0xFF;
    return payload;
}
void NetworkInterfaceTest::TestNetworkCommand::decode_payload(std::vector<unsigned char> command_data) {
    some_payload = command_data[0] << 24
                 | command_data[1] << 16
                 | command_data[2] << 8
                 | command_data[3] << 0;
}

void NetworkInterfaceTest::setUp()
{
    NetworkInterface::add_network_command(new TestNetworkCommand());
}


void NetworkInterfaceTest::tearDown()
{
}

void NetworkInterfaceTest::encode_command_test()
{
    TestNetworkCommand test_command;
    test_command.some_payload = 0x12345678;
    auto vector = NetworkInterface::encode_command(test_command);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0xEF, vector[0]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x00, vector[1]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x08, vector[2]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x12, vector[3]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x34, vector[4]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x56, vector[5]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0x78, vector[6]);
    CPPUNIT_ASSERT_EQUAL((unsigned char)0xCD, vector[7]);
}

void NetworkInterfaceTest::decode_command_test()
{
    const int payload = 0x12345678;
    TestNetworkCommand test_command;
    test_command.some_payload = payload;
    NetworkCommand& network_command = NetworkInterface::decode_command(NetworkInterface::encode_command(test_command));
    int decoded_payload = dynamic_cast<TestNetworkCommand*>(&network_command)->some_payload;
    CPPUNIT_ASSERT_EQUAL(payload, decoded_payload);
 
}


