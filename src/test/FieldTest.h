#ifndef _FIELDTEST_H
#define _FIELDTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <common/Field.h>

class FieldTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(FieldTest);

    CPPUNIT_TEST(test_hit);
    CPPUNIT_TEST(test_position);

    CPPUNIT_TEST_SUITE_END();

    private:
        Field *field;
      
    public:
        void setUp();
        void tearDown();
          
        void test_hit();
        void test_position();

};

#endif  // FIELDTEST_H
