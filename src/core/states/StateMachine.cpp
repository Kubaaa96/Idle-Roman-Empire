#include "StateMachine.h"

namespace ire::core::state
{
    StateMachine::StateMachine()
        : m_resume{ false }
        , m_running{ false }
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
        if (m_resume)
        {
            if (!m_states.empty())
            {
                m_states.pop();
            }

            if (!m_states.empty())
            {
                m_states.top()->resume();
            }

            m_resume = false;
        }

        if (!m_states.empty())
        {
            auto temp = m_states.top()->next();

            if (temp != nullptr)
            {
                if (temp->isReplacing())
                {
                    m_states.pop();
                }
                else
                {
                    m_states.top()->pause();
                }
                
                m_states.push(std::move(temp));
            }
        }
    }

    void StateMachine::lastState()
    {
        m_resume = true;
    }

    void StateMachine::draw()
    {
        m_states.top()->draw();
    }

    bool StateMachine::running() const
    {
        return m_running;
    }

    void StateMachine::quit()
    {
        m_running = false;
    }
}