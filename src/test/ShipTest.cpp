#include "ShipTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ShipTest);


void ShipTest::setUp()
{
    std::list<std::shared_ptr<Field>> fields1;
    fields1.push_back(std::shared_ptr<Field>(new Field(position(0, 1))));
    fields1.push_back(std::shared_ptr<Field>(new Field(position(0, 2))));
    ship1 = new Ship(fields1);

    std::list<std::shared_ptr<Field>> fields2;
    fields2.push_back(std::shared_ptr<Field>(new Field(position(1, 1))));
    fields2.push_back(std::shared_ptr<Field>(new Field(position(2, 1))));
    fields2.push_back(std::shared_ptr<Field>(new Field(position(3, 1))));
    fields2.push_back(std::shared_ptr<Field>(new Field(position(4, 1))));
    fields2.push_back(std::shared_ptr<Field>(new Field(position(5, 1))));
    ship2 = new Ship(fields2);
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


