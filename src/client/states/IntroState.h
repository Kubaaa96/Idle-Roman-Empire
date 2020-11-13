#ifndef IRE_INTROSTATE_H
#define IRE_INTROSTATE_H

#include "core/states/State.h"

namespace ire::client::state
{
    struct IntroState : core::state::State
    {
        core::gui::Group* drawGUI() override;

    };
}

#endif // !IRE_INTROSTATE_H
