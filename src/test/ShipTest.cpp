#include "ShipTest.h"
#include <common/Ship.h>
#include <common/Field.h>
#include <common/BattleField.h>
#include <common/position.h>
#include <common/GameConfiguration.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ShipTest);


void ShipTest::setUp()
{
    config = new GameConfiguration();
    battle_field = new BattleField(*config);
    ship1 = new Ship(2, ORIENTATION_HORIZONTAL, position(0, 0), *battle_field);

    ship2 = new Ship(5, ORIENTATION_VERTICAL, position(1, 1), *battle_field);
}


void ShipTest::tearDown()
{
    delete ship1;
    delete ship2;
    delete battle_field;
    delete config;
}

void ShipTest::test_length()
{
    CPPUNIT_ASSERT_EQUAL(2, (int)ship1->get_length());
    CPPUNIT_ASSERT_EQUAL(5, (int)ship2->get_length());
}

void ShipTest::test_ship_parts()
{
    Field &field = **std::next(std::next(std::next(ship2->get_ship_parts().begin()))); // 4th element
    position_t position = field.get_position(); 
    CPPUNIT_ASSERT_EQUAL(4, (int)position.y);
    CPPUNIT_ASSERT_EQUAL(1, (int)position.x);
}

void ShipTest::test_is_destroyed()
{
    CPPUNIT_ASSERT(!ship2->is_destroyed());

    Field &field = **std::next(std::next(std::next(ship2->get_ship_parts().begin()))); // 4th element
    field.set_hit();

    CPPUNIT_ASSERT(!ship2->is_destroyed());

    auto parts = ship2->get_ship_parts();
    for(auto it = parts.begin(); it != parts.end(); it++) {
        Field &field = **it;
        field.set_hit();
    }

    CPPUNIT_ASSERT(ship2->is_destroyed());
}


