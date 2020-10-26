#include "Engine.h"

namespace ire::core {

    Engine::Engine(sf::RenderWindow& window)
        : m_window(window)
    {
        group = ire::core::widgets::Group::create({ 200, 200 });
        group->setPosition({ 100, 100 });
        std::unique_ptr<ire::core::widgets::Button> btn1Ptr =
            ire::core::widgets::Button::create("test");
        std::unique_ptr<ire::core::widgets::Button> btn2Ptr =
            ire::core::widgets::Button::create("test1");

        btn1Ptr->setSize({ 50, 50 });
        btn1Ptr->setPosition({ 50, 0 }); // Adding 100 + 50 on x
        group->add(std::move(btn1Ptr), "Button1");
        btn2Ptr->setSize({ 50, 50 });
        btn2Ptr->setPosition({ 0, 50 });
        group->add(std::move(btn2Ptr), "Button2");

 
        //group->get("Button1")->setPosition({ 500, 500 });
        //printf(group->remove("Button1") ? "True" : "False");


    }

    void Engine::run()
    {
        sf::CircleShape shape(100.F);
        shape.setFillColor(sf::Color::Green);

        group->init();

        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_window.clear();
            m_window.draw(shape);
            group->draw(m_window);
            m_window.display();
        }
    }

}
