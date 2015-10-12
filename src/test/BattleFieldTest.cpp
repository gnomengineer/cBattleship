#include "BattleFieldTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BattleFieldTest);


void BattleFieldTest::setUp()
{
    battleField = new BattleField(10, 10);
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

void BattleFieldTest::test_all_ships_destroyed()
{
    CPPUNIT_ASSERT(battleField->all_ships_destroyed());
    CPPUNIT_ASSERT_NO_THROW(battleField->add_ship(2, ORIENTATION_VERTICAL, position(0, 0)));
    CPPUNIT_ASSERT(!battleField->all_ships_destroyed());
    battleField->hit_field(position(0, 0));
    battleField->hit_field(position(1, 0));
    CPPUNIT_ASSERT(battleField->all_ships_destroyed());
}


