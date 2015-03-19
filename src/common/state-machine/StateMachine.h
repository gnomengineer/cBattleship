#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <map>


template<typename E, class M, class I> 
class StateMachine {
    public:
        typedef E (M::*StateFuncPtr)(I input);
        typedef std::map<E, StateFuncPtr> StateMap;

    protected:
        std::map<E, StateFuncPtr> state_map;
        M & instance;
        E current_state;

    public:
        StateMachine(E initial_state, M & instance) 
            : state_map(instance.get_state_map()), instance(instance), current_state(initial_state) {
        }

        virtual ~StateMachine() {}

        E run_state(I input) {
            return current_state = run_single_state(input);
        }

        E get_current_state() {
            return current_state;
        }

        bool has_terminated() {
            return is_end_state(current_state);
        }

    protected:
        E run_single_state(I input) {
            auto fptr_found = state_map.find(current_state);
            if(fptr_found == state_map.end()) return static_cast<E>(-1);
            auto fptr = fptr_found->second;
            return (instance.*fptr)(input);
        }

        bool is_end_state(E state) {
            return (int)state < 0;
        }
};

#endif /* _STATE_MACHINE */
