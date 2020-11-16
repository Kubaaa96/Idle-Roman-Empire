#include "State.h"

namespace ire::core::state
{
    State::State(StateMachine& stateMachine, gui::SystemWindow& window, bool replace)
        : m_stateMachine{ stateMachine }
        , m_window{ window }
        , m_replacing{ replace }
    {
    }
    std::unique_ptr<State> State::next()
    {
        return std::move(m_next);
    }
    bool State::isReplacing() const
    {
        return m_replacing;
    }
}