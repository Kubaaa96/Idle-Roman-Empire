#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "gui/widgets/Button.h"
#include "gui/widgets/Label.h"
#include "gui/widgets/EditBox.h"
#include "gui/widgets/Panel.h"
#include "gui/widgets/HorizontalLayout.h"
#include "gui/widgets/VerticalLayout.h"
#include <memory>

namespace ire::core {

    struct Engine {
        Engine(sf::RenderWindow& window);

        void run();

    private:
        sf::RenderWindow& m_window;
        std::unique_ptr<ire::core::gui::Group> group;
        std::unique_ptr<ire::core::gui::Panel> panel;
        std::unique_ptr<ire::core::gui::HorizontalLayout> horizontalLayout;
        std::unique_ptr<ire::core::gui::VerticalLayout> verticalLayout;
    };

}

#endif // !ENGINE_H
