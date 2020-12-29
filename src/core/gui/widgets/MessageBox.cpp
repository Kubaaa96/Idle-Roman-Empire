#include "MessageBox.h"
#include <iostream>

namespace ire::core::gui
{
    WidgetType const MessageBox::m_type = WidgetType::create<MessageBox>("MessageBox");
    MessageBox::MessageBox()
    {
        m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "");
    }

    std::unique_ptr<MessageBox> MessageBox::create(const std::string& title)
    {
        auto widget = std::make_unique<MessageBox>();
        widget->setTitle(title);
        return widget;
    }

    void MessageBox::processMessageBox()
    {
        while (m_window.isOpen())
        {
            m_group->draw(m_window);
            display();

            processEvents();
        }
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

    void MessageBox::setWindowWidth(unsigned int windowWidth)
    {
        if (m_windowWidth != windowWidth)
        {
            m_windowWidth = windowWidth;
            m_window.setSize({ m_windowWidth, m_window.getSize().y });
        }
    }

    const unsigned int MessageBox::getWindowWidth() const
    {
        return m_windowWidth;
    }

    void MessageBox::setWindowHeight(unsigned int windowHeight)
    {
        if (m_windowHeight != windowHeight)
        {
            m_windowHeight = windowHeight;
            m_window.setSize({ m_window.getSize().x , m_windowHeight});
        }
    }

    const unsigned int MessageBox::getWindowHeight() const
    {
        return m_windowHeight;
    }

    void MessageBox::setWindowSize(unsigned int windowWidth, unsigned int windowHeight)
    {
        if (m_windowWidth != windowWidth || m_windowHeight != windowHeight)
        {
            m_windowWidth = windowWidth;
            m_windowHeight = windowHeight;
            m_window.setSize({ m_windowWidth, m_windowHeight });
        }
    }

    void MessageBox::setWindowSize(sf::Vector2u windowSize)
    {
        if (m_windowWidth != windowSize.x || m_windowHeight != windowSize.y)
        {
            m_windowWidth = windowSize.x;
            m_windowHeight = windowSize.y;
            m_window.setSize(windowSize);
        }
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