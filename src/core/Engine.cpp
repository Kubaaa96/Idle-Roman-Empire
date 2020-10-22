#include "Engine.h"

namespace ire::core {

    Engine::Engine(sf::RenderWindow& window)
        : m_window(window)
    {
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
            m_window.display();
            //shape.setPosition(shape.getPosition().x + 1, shape.getPosition().y);
        }
    }

}
