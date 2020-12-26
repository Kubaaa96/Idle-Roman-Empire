#ifndef IRE_MENUSTATE_H
#define IRE_MENUSTATE_H

#include "core/states/State.h"

namespace ire::core::gui
{
    struct SystemWindow;
}

namespace ire::core::state
{
    struct StateMachine;
}

namespace ire::client::state
{
    struct MenuState : core::state::State
    {
        MenuState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace);

        void initializeGUI() override;

    private:
    };
}

#endif // !IRE_MENUSTATE_H
