#ifndef _BATTLEFIELDTEST_H
#define _BATTLEFIELDTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <common/BattleField.h>

class BattleFieldTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BattleFieldTest);

    CPPUNIT_TEST(test_add_ship_length);
    CPPUNIT_TEST(test_add_ship_position);
    CPPUNIT_TEST(test_add_ship_over_border);
    CPPUNIT_TEST(test_add_ship_collision);
    CPPUNIT_TEST(test_all_ships_destroyed);

    CPPUNIT_TEST_SUITE_END();

    private:
        GameConfiguration *config;
        BattleField *battleField;
      
    public:
        void setUp();
        void tearDown();
          
        void test_add_ship_length();
        void test_add_ship_position();
        void test_add_ship_over_border();
        void test_add_ship_collision();
        void test_add_ship();
        void test_all_ships_destroyed();

};

#endif  // BATTLEFIELDTEST_H
