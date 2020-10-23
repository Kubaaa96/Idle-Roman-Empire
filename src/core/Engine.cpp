#include "Engine.h"

namespace ire::core {

    Engine::Engine(sf::RenderWindow& window)
        : m_window(window)
        , containerPtr(std::make_unique<ire::core::widgets::Container>())
    {
        std::unique_ptr<ire::core::widgets::Button> btn1Ptr = std::make_unique< ire::core::widgets::Button>();
        std::unique_ptr<ire::core::widgets::Button> btn2Ptr = std::make_unique< ire::core::widgets::Button>();
        containerPtr->add(std::move(btn1Ptr));
        containerPtr->getWidgets()[0]->setSize({ 100, 100 });
        containerPtr->getWidgets()[0]->setPosition({ 100, 100 });

        containerPtr->add(std::move(btn2Ptr));
        containerPtr->getWidgets()[1]->setSize({ 50, 50 });
        containerPtr->getWidgets()[1]->setPosition({ 500, 100 });
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
            containerPtr->draw(m_window);
            m_window.display();
        }
    }

}
