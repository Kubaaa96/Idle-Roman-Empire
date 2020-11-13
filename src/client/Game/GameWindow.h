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

namespace ire::client {

    struct GameWindow : core::gui::SystemWindow
    {
        using BaseType = core::gui::SystemWindow;

        template <typename... Ts>
        GameWindow(Ts&&... args) :
            BaseType(std::forward<Ts>(args)...)
        {
            // StateMachine runinng current state
            //auto introState = std::make_unique<state::IntroState>();
            //setCurrentState(introState);
            init();
        }

    private:
        std::unique_ptr<ire::core::gui::Group> group;
        std::unique_ptr<ire::core::gui::Panel> panel;
        std::unique_ptr<ire::core::gui::Panel> panel2;
        std::unique_ptr<ire::core::gui::HorizontalLayout> horizontalLayout;
        std::unique_ptr<ire::core::gui::VerticalLayout> verticalLayout;

        void init();
    };

}

#endif // !IRE_GAME_WINDOW_H
