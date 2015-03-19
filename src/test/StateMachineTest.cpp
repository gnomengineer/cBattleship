#include "StateMachineTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(StateMachineTest);

StateMachineTest::LeetStateMachine::LeetStateMachine(std::vector<int> numbers)
    : numbers(numbers), idx(0), have_three(false) {
}

StateMachineTest::LeetStateMachine::StateMap StateMachineTest::LeetStateMachine::get_state_map() {
    LeetStateMachine::StateMap m;
    m[ONE] = &LeetStateMachine::state_one;
    m[THREE] = &LeetStateMachine::state_three;
    m[SEVEN] = &LeetStateMachine::state_seven;
    m[END] = &LeetStateMachine::state_end;
    return m;
}

int StateMachineTest::LeetStateMachine::get_input() {
    if(idx < numbers.size()) {
        return numbers[idx++];
    }
    return -1;
}

StateMachineTest::LeetState StateMachineTest::LeetStateMachine::state_one(int in) {
    if(in == 1) return THREE;
    if(in == 0) return END;
    else return ONE;
}
StateMachineTest::LeetState StateMachineTest::LeetStateMachine::state_three(int in) {
    if(in == 3) {
        if(have_three) {
            have_three = false;
            return SEVEN;
        } else {
            have_three = true;
            return THREE;
        }
    }
    if(in == 0) return END;
    else return THREE;
}
StateMachineTest::LeetState StateMachineTest::LeetStateMachine::state_seven(int in) {
    if(in == 1) return END;
    if(in == 0) return END;
    else return SEVEN;
}
StateMachineTest::LeetState StateMachineTest::LeetStateMachine::state_end(int in) {
    return END;
}


void StateMachineTest::setUp()
{
    std::vector<int> numbers = {1, 3, 3, 7, 0};
    leet_state_machine1 = new LeetStateMachine(numbers);
    state_machine = new StateMachine<LeetState, LeetStateMachine, int>(ONE, *leet_state_machine1);
}


void StateMachineTest::tearDown()
{
    delete state_machine;
    delete leet_state_machine1;
}

void StateMachineTest::run_state()
{
    int i = 1;
    state_machine->run_state(i);
}



