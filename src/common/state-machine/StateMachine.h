#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <map>

template<typename E, class M, class I> 
class StateMachine {
    private:
        typedef E (M::*StateFuncPtr)(I input);
        std::map<E, StateFuncPtr> state_map;
        M & instance;
        E current_state;

    public:
        StateMachine(E initial_state, M & instance) 
            : state_map(instance.get_state_map()), instance(instance), current_state(initial_state) {
        }

        virtual ~StateMachine() {}

        E run() {
            while(!is_end_state(current_state)) {
                run_state(instance.get_input());
            }
        }

        E run_state(I & input) {
            return current_state = run_single_state(input);
        }

    private:
        E run_single_state(I & input) {
            auto fptr = state_map.find(current_state);
            if(fptr == state_map.end()) return -1;
            return (instance.*fptr)(input);
        }

        bool is_end_state(E state) {
            return (int)state < 0;
        }
};
#endif /* _STATE_MACHINE */
