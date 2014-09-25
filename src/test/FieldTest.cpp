#include "FieldTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(FieldTest);


void FieldTest::setUp()
{
    field = new Field(position(23, 123));
}


void FieldTest::tearDown()
{
    delete field;
}

void FieldTest::test_hit()
{
    CPPUNIT_ASSERT(field->is_hit() == false);
    field->set_hit();
    CPPUNIT_ASSERT(field->is_hit() == true);
}

void FieldTest::test_position()
{
    position position = field->get_position();
    CPPUNIT_ASSERT(position.y == 23);
    CPPUNIT_ASSERT(position.x == 123);
}


