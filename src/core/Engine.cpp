#include "Engine.h"
#include <iostream>

namespace ire::core {

    Engine::Engine(sf::RenderWindow& window)
        : m_window(window)
    {
        horizontalLayout = ire::core::widgets::HorizontalLayout::create({ 500,400 });
        horizontalLayout->setPosition({ 100, 100 });
        std::unique_ptr<ire::core::widgets::Button> btn1Ptr =
            ire::core::widgets::Button::create("test");
        std::unique_ptr<ire::core::widgets::Button> btn2Ptr =
            ire::core::widgets::Button::create("test1");
        std::unique_ptr<ire::core::widgets::Button> btn3Ptr =
            ire::core::widgets::Button::create("test");
        std::unique_ptr<ire::core::widgets::Button> btn4Ptr =
            ire::core::widgets::Button::create("test1");

        horizontalLayout->add(std::move(btn1Ptr), "Button1");

        horizontalLayout->add(std::move(btn2Ptr), "Button2");
        horizontalLayout->add(std::move(btn3Ptr), "Button3");
        horizontalLayout->add(std::move(btn4Ptr), "Button4");
        horizontalLayout->setSpaces(10);
        horizontalLayout->setMargins({ 5, 5, 10, 10 });
        if (!horizontalLayout->remove("Button3"))
        {
            std::cout << "Cannot remove object named: Button3";
        }
    }

    void Engine::run()
    {
        sf::CircleShape shape(100.F);
        shape.setFillColor(sf::Color::Green);

        //group->init();

        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_window.clear();
            m_window.draw(shape);
            horizontalLayout->draw(m_window);
            m_window.display();
        }
    }

}
