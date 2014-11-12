#ifndef _NETWORKINTERFACETEST_H
#define _NETWORKINTERFACETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <common/communication/NetworkCommand.h>
#include <common/communication/NetworkInterface.h>

class NetworkInterfaceTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(NetworkInterfaceTest);

    CPPUNIT_TEST(encode_command_test);
    CPPUNIT_TEST(decode_command_test);

    CPPUNIT_TEST_SUITE_END();

    private:
        NetworkInterface *network_interface;

        class TestNetworkCommand : public NetworkCommand {
            public:
                int some_payload;
                virtual command_nr_t get_command_nr();
                virtual std::vector<unsigned char> encode_payload();
                virtual void decode_payload(std::vector<unsigned char> command_data);
        };
      
    public:
        void setUp();
        void tearDown();
          
        void encode_command_test();
        void decode_command_test();

};

#endif  // NETWORKINTERFACETEST_H
