#ifndef IRE_STATEMACHINE_H
#define IRE_STATEMACHINE_H

#include "State.h"

#include <memory>
#include <stack>
#include <iostream>

namespace ire::core::gui
{
    struct SystemWindow;
}

namespace ire::core::state
{
    struct StateMachine
    {
        StateMachine();
        void run(std::unique_ptr<State> state);

        void nextState();

        void draw();

        bool running() const;
        void quit();

    private:
        // The stack of states
        std::stack<std::unique_ptr<State>> m_states;

        bool m_running;
    };
}


#endif //!IRE_STATEMACHINE_H