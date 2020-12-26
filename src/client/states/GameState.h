#ifndef IRE_GAMESTATE_H
#define IRE_GAMESTATE_H

#include "core/states/State.h"
#include "core/gui/widgets/Button.h"
#include "core/gui/widgets/Label.h"
#include "core/gui/widgets/EditBox.h"
#include "core/gui/widgets/Panel.h"
#include "core/gui/widgets/ProgressBar.h"
#include "core/gui/widgets/HorizontalLayout.h"
#include "core/gui/widgets/VerticalLayout.h"

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
    // Temporary State in future there will be state for each different Action involving 
    // different GUI and behaviour like Different industries 
    struct GameState : core::state::State
    {
        GameState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace);

        void initializeGUI() override;

    private:

    };
}

#endif // !IRE_GAMESTATE_H