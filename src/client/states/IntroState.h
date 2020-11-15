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
        IntroState(core::state::StateMachine& machine, core::gui::SystemWindow& window, bool replace = true);

        void pause() override;
        void resume() override;

        void draw() override;

        core::gui::Group* drawGUI() override;
    private:
        std::unique_ptr<ire::core::gui::Group> group;
    };
}

#endif // !IRE_INTROSTATE_H
