#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "widgets/Widget.h"
#include <memory>

namespace ire::core {

    struct Engine {
        Engine(sf::RenderWindow& window);

        void run();

    private:
        sf::RenderWindow& m_window;
        //std::unique_ptr<ire::core::widgets::Widget> widgetPtr;
    };

}

#endif // !ENGINE_H
