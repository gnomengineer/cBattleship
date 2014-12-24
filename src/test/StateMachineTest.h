#ifndef _STATEMACHINETEST_H
#define _STATEMACHINETEST_H

#include <cppunit/extensions/HelperMacros.h>

class StateMachineTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StateMachineTest);

    CPPUNIT_TEST(initialization);
    CPPUNIT_TEST(run);
    CPPUNIT_TEST(run_state);
    CPPUNIT_TEST(is_end_state);

    CPPUNIT_TEST_SUITE_END();

    enum LeetState {
        ONE = 1,
        THREE = 3,
        SEVEN = 7,
        END = -1
    };

    class LeetStateMachine {
        private:
            std::vector<int> numbers;
            int idx;

        public:
            LeetStateMachine(std::vector numbers);
            std::map<LeetState, int> get_state_map();
            int get_input();

            LeetState state_one(int in);
            LeetState state_three(int in);
            LeetState state_seven(int in);
            LeetState state_end(int in);
    };

    LeetStateMachine* leet_state_machine1;
    LeetStateMachine* leet_state_machine2;
    StateMachine<LeetState, LeetStateMachine, int>* state_machine;
      
    public:
        void setUp();
        void tearDown();
          
        void initialization();
        void run();
        void run_state();
        void is_end_state();

};

#endif  // STATEMACHINETEST_H
