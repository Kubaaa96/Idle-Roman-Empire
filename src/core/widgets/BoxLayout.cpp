#include "BoxLayout.h"

#include <iostream>

namespace ire::core::widgets
{
    BoxLayout::BoxLayout(const sf::Vector2f& size)
        : Group{size}
    {

    }
    void BoxLayout::setSize(const sf::Vector2f& size)
    {
        Container::setSize(size);

        updateWidgets();
    }
    void BoxLayout::add(std::unique_ptr<Widget> widgetPtr, const std::string& widgetName)
    {
        insert(m_widgets.size(), std::move(widgetPtr), widgetName);
        updateWidgets();
    }
    void BoxLayout::insert(std::size_t index, std::unique_ptr<Widget>& widgetPtr, const std::string& widgetName)
    {
        if (index < m_widgets.size())
        {
            m_widgets.insert(m_widgets.begin() + index, std::move(widgetPtr));
        }
        else
        {
            Group::add(std::move(widgetPtr), widgetName);
        }
    }
    bool BoxLayout::remove(const std::string& widgetName)
    {
        if (Group::remove(widgetName))
        {
            updateWidgets();
            return true;
        }
        return false;
    }
    
}