#ifndef _SHIPTEST_H
#define _SHIPTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <common/BattleField.h>
#include <common/Ship.h>

class ShipTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ShipTest);

    CPPUNIT_TEST(test_length);
    CPPUNIT_TEST(test_ship_parts);
    CPPUNIT_TEST(test_is_destroyed);

    CPPUNIT_TEST_SUITE_END();

    private:
        BattleField battle_field;
        Ship *ship1;
        Ship *ship2;
      
    public:
        void setUp();
        void tearDown();
          
        void test_length();
        void test_ship_parts();
        void test_is_destroyed();

};

#endif  // SHIPTEST_H
