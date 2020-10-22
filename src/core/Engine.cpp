#include "Engine.h"

namespace ire::core {

    Engine::Engine(sf::RenderWindow& window)
        : m_window(window)
        , widgetPtr(std::make_unique<ire::core::widgets::Widget>())
    {
        widgetPtr->setPosition(100, 100);
        widgetPtr->setSize(50, 50);
        widgetPtr->setOrigin(0, 0);
    }

    void Engine::run()
    {
        sf::CircleShape shape(100.F);
        shape.setFillColor(sf::Color::Green);

        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_window.clear();
            m_window.draw(shape);
            widgetPtr->drawRect(m_window);
            m_window.display();
            //shape.setPosition(shape.getPosition().x + 1, shape.getPosition().y);
        }
    }

}
