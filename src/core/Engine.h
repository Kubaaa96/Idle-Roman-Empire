#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "widgets/Button.h"
#include "widgets/Container.h"
#include "widgets/Group.h"
#include <memory>

namespace ire::core {

    struct Engine {
        Engine(sf::RenderWindow& window);

        void run();

    private:
        sf::RenderWindow& m_window;
        std::unique_ptr<ire::core::widgets::Group> group;
    };

}

#endif // !ENGINE_H
