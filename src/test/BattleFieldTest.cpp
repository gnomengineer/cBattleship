#include "BattleFieldTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BattleFieldTest);


void BattleFieldTest::setUp()
{
    battleField = new BattleField();
}


void BattleFieldTest::tearDown()
{
    delete battleField;
}

void BattleFieldTest::test_add_ship_length()
{
    CPPUNIT_ASSERT_THROW(battleField->add_ship(0, ORIENTATION_VERTICAL, position(0, 0)), std::invalid_argument);
    CPPUNIT_ASSERT_THROW(battleField->add_ship(6, ORIENTATION_VERTICAL, position(0, 0)), std::invalid_argument);
    CPPUNIT_ASSERT_NO_THROW(battleField->add_ship(5, ORIENTATION_VERTICAL, position(0, 0)));
    CPPUNIT_ASSERT_THROW(battleField->add_ship(5, ORIENTATION_VERTICAL, position(1, 1)), std::invalid_argument);
}

void BattleFieldTest::test_add_ship_position()
{
    CPPUNIT_ASSERT_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(123, 0)), std::out_of_range);
    CPPUNIT_ASSERT_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(0, 11)), std::out_of_range);
    CPPUNIT_ASSERT_NO_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(2, 9)));
}

void BattleFieldTest::test_add_ship_over_border()
{
    CPPUNIT_ASSERT_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(9, 0)), std::out_of_range);
    CPPUNIT_ASSERT_NO_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(8, 0)));
}

void BattleFieldTest::test_add_ship_collision()
{
    CPPUNIT_ASSERT_NO_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(0, 0)));
    CPPUNIT_ASSERT_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(1, 0)), std::invalid_argument);
    CPPUNIT_ASSERT_NO_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(2, 0)));
}

void BattleFieldTest::test_add_ship()
{
    CPPUNIT_ASSERT_NO_THROW(battleField->add_ship(2, ORIENTATION_HORIZONTAL, position(3, 4)));
    CPPUNIT_FAIL("not fully implemented yet");
    // need a function to retrieve ships
    
}

void BattleFieldTest::test_all_ships_destroyed()
{
    CPPUNIT_FAIL("not implemented yet");
}


