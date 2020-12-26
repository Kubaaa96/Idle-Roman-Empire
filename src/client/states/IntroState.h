#ifndef IRE_INTROSTATE_H
#define IRE_INTROSTATE_H

#include "core/states/State.h"
#include "core/gui/widgets/Group.h"
#include "core/gui/widgets/Button.h"

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
    struct IntroState : core::state::State
    {
        IntroState(core::state::StateMachine& machine, core::gui::SystemWindow& window, bool replace);

        void initializeGUI() override;
    private:
    };
}

#endif // !IRE_INTROSTATE_H
