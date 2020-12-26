#include "State.h"
#include "core/gui/SystemWindow.h"

namespace ire::core::state
{
    State::State(StateMachine& stateMachine, gui::SystemWindow& window, bool replace)
        : m_stateMachine{ stateMachine }
        , m_window{ window }
        , m_replacing{ replace }
    {
    }
    void State::draw()
    {
        auto& renderTarget = m_window.getRenderTarget();
        renderTarget.clear();

        if (m_group)
        {
            m_group->draw(renderTarget);
        }
    }
    std::unique_ptr<State> State::next()
    {
        return std::move(m_next);
    }
    bool State::isReplacing() const
    {
        return m_replacing;
    }
    ire::core::gui::Group* State::getGroup()
    {
        return m_group.get();
    }
}