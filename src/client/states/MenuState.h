#ifndef IRE_MENUSTATE_H
#define IRE_MENUSTATE_H

#include "core/states/State.h"

namespace ire::client::state
{
    struct MenuState : core::state::State
    {
        core::gui::Group* drawGUI() override;

    private:
        std::unique_ptr<ire::core::gui::Group> group;
    };
}

#endif // !IRE_MENUSTATE_H
