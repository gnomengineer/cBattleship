#ifndef _SHIPTEST_H
#define _SHIPTEST_H

#include <cppunit/extensions/HelperMacros.h>

class GameConfiguration;
class BattleField;
class Ship;

class ShipTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ShipTest);

    CPPUNIT_TEST(test_length);
    CPPUNIT_TEST(test_ship_parts);
    CPPUNIT_TEST(test_is_destroyed);

    CPPUNIT_TEST_SUITE_END();

    private:
        GameConfiguration *config;
        BattleField *battle_field;
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
