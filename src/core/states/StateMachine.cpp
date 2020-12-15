#include "StateMachine.h"

namespace ire::core::state
{
    StateMachine::StateMachine()
        : m_running{ false }
    {
        std::cout << "StateMachine Init\n";
    }

    void StateMachine::run(std::unique_ptr<State> state)
    {
        m_running = true;

        m_states.push(std::move(state));
    }

    void StateMachine::nextState()
    {
        if (!m_states.empty())
        {
            auto temp = m_states.top()->next();

            if (temp != nullptr)
            {
                if (temp->isReplacing())
                {
                    m_states.pop();
                }
                
                m_states.push(std::move(temp));
            }
        }
    }

    void StateMachine::draw()
    {
        m_states.top()->draw();
    }

    bool StateMachine::running() const
    {
        return m_running;
    }

    ire::core::gui::Group* StateMachine::getTopStateGroup()
    {
        return m_states.top()->getGroup();
    }

    void StateMachine::quit()
    {
        m_running = false;
    }
}