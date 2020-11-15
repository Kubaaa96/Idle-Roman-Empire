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
        State(StateMachine& machine, gui::SystemWindow& window, bool replace = true);
        virtual ~State() = default;

        State(const State&) = delete;
        State& operator=(const State&) = delete;
        virtual gui::Group* drawGUI() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void draw() = 0;

        std::unique_ptr<State> next();

        bool isReplacing() const;

    protected:
        StateMachine& m_machine;
        gui::SystemWindow& m_window;

        bool m_replacing;

        std::unique_ptr<State> m_next;
    };
}

#endif // !IRE_STATE_H