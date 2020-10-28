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
        std::unique_ptr<ire::core::widgets::Label> label7Ptr =
            ire::core::widgets::Label::create("test");
        std::unique_ptr<ire::core::widgets::EditBox> editBox8Ptr =
            ire::core::widgets::EditBox::create("test1");

        verticalLayout->add(std::move(btn5Ptr), "Button5");
        verticalLayout->add(std::move(btn6Ptr), "Button6");
        verticalLayout->add(std::move(label7Ptr), "Label1");
        verticalLayout->add(std::move(editBox8Ptr), "EditBox1");

        horizontalLayout = ire::core::widgets::HorizontalLayout::create({ 500,400 });
        //horizontalLayout->setPosition({ 100, 100 });
        horizontalLayout->setSpaces(10);
        std::unique_ptr<ire::core::widgets::EditBox> editBox1Ptr =
            ire::core::widgets::EditBox::create("test");
        std::unique_ptr<ire::core::widgets::Button> btn2Ptr =
            ire::core::widgets::Button::create("test1");
        std::unique_ptr<ire::core::widgets::Label> label3Ptr =
            ire::core::widgets::Label::create("test");
        std::unique_ptr<ire::core::widgets::Button> btn4Ptr =
            ire::core::widgets::Button::create("test1");

        horizontalLayout->add(std::move(editBox1Ptr), "EditBox2");
        horizontalLayout->add(std::move(btn2Ptr), "Button2");
        horizontalLayout->add(std::move(verticalLayout), "VerticalLayout");
        horizontalLayout->add(std::move(label3Ptr), "Label2");
        horizontalLayout->add(std::move(btn4Ptr), "Button4");

        horizontalLayout->setMargins({ 10, 10, 10, 10 });

        panel = ire::core::widgets::Panel::create({ 700, 400 }, std::move(horizontalLayout), std::string("HorizontalLayout"));
        panel->setPosition({200, 200});
        panel->setOpacity(200);
        panel->setOutlineColor(sf::Color::Magenta);
        panel->setOutlineThickness(7);
    }

    void Engine::run()
    {
        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_window.clear();
            panel->draw(m_window);
            //horizontalLayout->draw(m_window);
            m_window.display();
        }
    }

}
