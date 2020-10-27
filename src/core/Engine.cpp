#include "Engine.h"
#include <iostream>

namespace ire::core {

    Engine::Engine(sf::RenderWindow& window)
        : m_window(window)
    {
        verticalLayout = ire::core::widgets::VerticalLayout::create({ 500, 400 });
        verticalLayout->setPosition({ 100, 100 });
        verticalLayout->setSpaces(5);
        verticalLayout->setMargins({ 0, 0, 15, 15 });
        std::unique_ptr<ire::core::widgets::Button> btn5Ptr =
            ire::core::widgets::Button::create("test");
        std::unique_ptr<ire::core::widgets::Button> btn6Ptr =
            ire::core::widgets::Button::create("test1");
        std::unique_ptr<ire::core::widgets::Button> btn7Ptr =
            ire::core::widgets::Button::create("test");
        std::unique_ptr<ire::core::widgets::Button> btn8Ptr =
            ire::core::widgets::Button::create("test1");


        verticalLayout->add(std::move(btn5Ptr), "Button5");
        verticalLayout->add(std::move(btn6Ptr), "Button6");
        verticalLayout->add(std::move(btn7Ptr), "Button7");
        verticalLayout->add(std::move(btn8Ptr), "Button8");

        horizontalLayout = ire::core::widgets::HorizontalLayout::create({ 500,400 });
        horizontalLayout->setPosition({ 100, 100 });
        horizontalLayout->setSpaces(10);
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
        horizontalLayout->add(std::move(verticalLayout), "VerticalLayout");
        //horizontalLayout->add(std::move(btn3Ptr), "Button3");
        horizontalLayout->add(std::move(btn4Ptr), "Button4");



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
            horizontalLayout->draw(m_window);
            //verticalLayout->draw(m_window);
            m_window.display();
        }
    }

}
