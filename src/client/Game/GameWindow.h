#ifndef IRE_GAME_WINDOW_H
#define IRE_GAME_WINDOW_H

#include "core/gui/SystemWindow.h"

#include "core/gui/widgets/Button.h"
#include "core/gui/widgets/Label.h"
#include "core/gui/widgets/EditBox.h"
#include "core/gui/widgets/Panel.h"
#include "core/gui/widgets/HorizontalLayout.h"
#include "core/gui/widgets/VerticalLayout.h"
#include "client/states/IntroState.h"
#include "core/states/StateMachine.h"

namespace ire::client {

    struct GameWindow : core::gui::SystemWindow
    {
        using BaseType = core::gui::SystemWindow;

        template <typename... Ts>
        GameWindow(Ts&&... args) :
            BaseType(std::forward<Ts>(args)...)
        {

            m_stateMachine.run(std::make_unique<state::IntroState>(m_stateMachine, *this, true));

        }
    private:

    };

}

#endif // !IRE_GAME_WINDOW_H
