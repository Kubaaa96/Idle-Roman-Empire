#include "MessageBox.h"
#include <iostream>

namespace ire::core::gui
{
    WidgetType const MessageBox::m_type = WidgetType::create<MessageBox>("MessageBox");
    MessageBox::MessageBox()
    {
        m_window.create(sf::VideoMode(600, 300), "");
    }

    std::unique_ptr<MessageBox> MessageBox::create(const std::string& title)
    {
        auto widget = std::make_unique<MessageBox>();
        widget->setTitle(title);
        return widget;
    }
    void MessageBox::processMessageBox()
    {
        std::string test = "TestMessageBox\n";
        while (m_window.isOpen())
        {
            std::cout << test;
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    m_window.close();
                }
            }
        }
        //return std::string();
    }
    void MessageBox::setTitle(const std::string& title)
    {
        if (m_title != title)
        {
            m_title = title;
            m_window.setTitle(m_title);
        }
    }
    const std::string MessageBox::getTitle() const
    {
        return m_title;
    }
}