#include "StateMachineTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(StateMachineTest);

StateMachineTest::LeetStateMachine::LeetStateMachine(std::vector numbers)
    : numbers(numbers), idx(0) {
}
std::map<LeetState, int> StateMachineTest::LeetStateMachine::get_state_map()
    std::map<LeetState, int> m;
    m[ONE] = state_one;
    m[THREE] = state_three;
    m[SEVEN] = state_seven;
    m[END] = state_end;
    return m;
}

int StateMachineTest::LeetStateMachine::get_input() {
    if(idx < numbers.size) {
        return numbers[i++];
    }
    return -1;
}

LeetState StateMachineTest::LeetStateMachine::state_one(int in) {
    if(in == 1) return THREE;
    else return END;
}
LeetState StateMachineTest::LeetStateMachine::state_three(int in) {
}
LeetState StateMachineTest::LeetStateMachine::state_seven(int in) {
}
LeetState StateMachineTest::LeetStateMachine::state_one(int in) {
}


void StateMachineTest::setUp()
{
}


void StateMachineTest::tearDown()
{
}

void StateMachineTest::initialization()
{
    CPPUNIT_FAIL("not implemented yet");
}

void StateMachineTest::run()
{
    CPPUNIT_FAIL("not implemented yet");
}

void StateMachineTest::run_state()
{
    CPPUNIT_FAIL("not implemented yet");
}

void StateMachineTest::is_end_state()
{
    CPPUNIT_FAIL("not implemented yet");
}


