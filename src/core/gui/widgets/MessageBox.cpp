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
       // std::string test = "TestMessageBox\n";
        while (m_window.isOpen())
        {
            //std::cout << test;
            m_group->draw(m_window);
            display();

            processEvents();
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

    void MessageBox::initializeUI(std::unique_ptr<Group> group)
    {
        group->setSize({
            static_cast<float>(m_window.getSize().x),
            static_cast<float>(m_window.getSize().y) });
        group->fitInSize();
        m_group = std::move(group);
        setRootGroup(*m_group);
    }


}   