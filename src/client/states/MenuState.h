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
        MenuState(core::state::StateMachine& machine, core::gui::SystemWindow& window, bool replace = true);

        void pause() override;
        void resume() override;

        void draw() override;

        core::gui::Group* drawGUI() override;

    private:
        std::unique_ptr<ire::core::gui::Group> group;
    };
}

#endif // !IRE_MENUSTATE_H
