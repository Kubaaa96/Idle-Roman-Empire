#ifndef IRE_GAMESTATE_H
#define IRE_GAMESTATE_H

#include "core/states/State.h"
#include "core/gui/widgets/Button.h"
#include "core/gui/widgets/Label.h"
#include "core/gui/widgets/EditBox.h"
#include "core/gui/widgets/Panel.h"
#include "core/gui/widgets/HorizontalLayout.h"
#include "core/gui/widgets/VerticalLayout.h"

namespace ire::client::state
{
    // Temporary State in future there will be state for each different Action involving 
    // different GUI and behaviour like Different industries 
    struct GameState : core::state::State
    {
        GameState(const sf::Vector2u sizeOfWindow);
        core::gui::Group* drawGUI() override;

    private:

        std::unique_ptr<ire::core::gui::Group> group;
        std::unique_ptr<ire::core::gui::Panel> panel;
        std::unique_ptr<ire::core::gui::Panel> panel2;
        std::unique_ptr<ire::core::gui::HorizontalLayout> horizontalLayout;
        std::unique_ptr<ire::core::gui::VerticalLayout> verticalLayout;
    };
}

#endif // !IRE_GAMESTATE_H