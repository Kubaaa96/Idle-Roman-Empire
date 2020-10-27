#include "Engine.h"

namespace ire::core {

    Engine::Engine(sf::RenderWindow& window)
        : m_window(window)
    {
        //group = ire::core::widgets::Group::create({ 500, 400 });
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

        //btn1Ptr->setSize({ 50, 50 });
        //btn1Ptr->setPosition({ 50, 0 }); // Adding 100 + 50 on x
        horizontalLayout->add(std::move(btn1Ptr), "Button1");
        //btn2Ptr->setSize({ 50, 50 });
        //btn2Ptr->setPosition({ 0, 50 });
        horizontalLayout->add(std::move(btn2Ptr), "Button2");
        horizontalLayout->add(std::move(btn3Ptr), "Button3");
        horizontalLayout->add(std::move(btn4Ptr), "Button4");

 
        //group->get("Button1")->setPosition({ 500, 500 });
        //printf(group->remove("Button1") ? "True" : "False");


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
