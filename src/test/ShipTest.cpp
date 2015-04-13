#include "ShipTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ShipTest);


void ShipTest::setUp()
{
    ShipData ship_data;
    ship_data.length = 2;
    ship_data.orientation = ORIENTATION_HORIZONTAL;
    ship_data.start_position = position(0, 0);
    ship1 = new Ship(ship_data, battle_field);

    ship2 = new Ship(5, ORIENTATION_VERTICAL, position(1, 1), battle_field);
}


void ShipTest::tearDown()
{
    delete ship1;
    delete ship2;
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


