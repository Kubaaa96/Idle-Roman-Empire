#ifndef IRE_STATE_H
#define IRE_STATE_H

#include "core/gui/widgets/Group.h"


namespace ire::core::gui
{
    struct SystemWindow;
}
namespace ire::core::state
{       
    struct StateMachine;

    struct State
    {
        State(StateMachine& stateMachine, gui::SystemWindow& window, bool replace);
        virtual ~State() = default;

        State(const State&) = delete;
        State& operator=(const State&) = delete;
        virtual void initializeGUI() = 0;

        virtual void draw();

        std::unique_ptr<State> next();

        bool isReplacing() const;

        ire::core::gui::Group* getGroup();

    protected:
        StateMachine& m_stateMachine;
        gui::SystemWindow& m_window;

        bool m_replacing;
        std::unique_ptr<ire::core::gui::Group> m_group;
        std::unique_ptr<State> m_next;
    };
}

#endif // !IRE_STATE_H