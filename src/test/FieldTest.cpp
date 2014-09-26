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
    CPPUNIT_ASSERT(!field->is_hit());
    field->set_hit();
    CPPUNIT_ASSERT(field->is_hit());
}

void FieldTest::test_position()
{
    position_t position = field->get_position();
    CPPUNIT_ASSERT_EQUAL(23, (int)position.y);
    CPPUNIT_ASSERT_EQUAL(123, (int)position.x);
}


