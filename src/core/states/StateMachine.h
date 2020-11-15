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
        void lastState();

        void draw();

        bool running() const;
        void quit();

        template <typename T>
        static std::unique_ptr<T> build(StateMachine& machine, gui::SystemWindow& window, bool replace = true);
    private:
        // The stack of states
        std::stack<std::unique_ptr<State>> m_states;

        bool m_resume;
        bool m_running;
    };
}

template <typename T>
std::unique_ptr<T> ire::core::state::StateMachine::build(ire::core::state::StateMachine& machine, ire::core::gui::SystemWindow& window, bool replace)
{
    return std::make_unique<T>(machine, window, replace);
}

#endif //!IRE_STATEMACHINE_H