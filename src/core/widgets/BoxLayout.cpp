#include "BoxLayout.h"

#include <iostream>
#include <numeric>
#include <initializer_list>
#include <algorithm>


namespace ire::core::widgets
{
    BoxLayout::BoxLayout(const sf::Vector2f& size)
        : Group{size}
    {

    }
    void BoxLayout::setSize(const sf::Vector2f& size, bool updateWidget)
    {
        Container::setSize(size);
        if(updateWidget)
            updateWidgets();
    }
    void BoxLayout::setPosition(const sf::Vector2f& position, bool updateWidget)
    {
        Container::setPosition(position);
        if(updateWidget)
            updateWidgets();
    }
    void BoxLayout::add(std::unique_ptr<Widget> widgetPtr, const std::string& widgetName)
    {
        insert(m_widgets.size(), std::move(widgetPtr), widgetName);
    }
    void BoxLayout::insert(std::size_t index, std::unique_ptr<Widget> widgetPtr, const std::string& widgetName)
    {
        if (index < m_widgets.size())
        {
            m_widgets.insert(m_widgets.begin() + index, std::move(widgetPtr));
        }
        else
        {
            Group::add(std::move(widgetPtr), widgetName);
        }
        updateWidgets();
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

    void BoxLayout::setMargins(const Margins& margins)
    {
        m_margins = margins;
        updateWidgets();
    }

    const Margins& BoxLayout::getMargins() const
    {
        return m_margins;
    }

    void BoxLayout::setSpaces(float spaces)
    {
        m_spaces = spaces;
    }

    const float BoxLayout::getSpaces()
    {
        return m_spaces;
        updateWidgets();
    }

    void BoxLayout::setLayoutStretch(std::initializer_list<int> list)
    {
        // Check if number of items in initializer_list is the same as m_widgets.size()
        if (list.size() != m_widgets.size())
        {
            std::cout << "Size of list and widget vector is different. Need to be the same\n";
            return;
        }
        m_layoutStretch = list;
        m_sumOfLayoutStretches = std::accumulate(m_layoutStretch.begin(), m_layoutStretch.end(), 0);

        updateWidgets();
    }

    const std::vector<int> BoxLayout::getLayoutStretch() const
    {
        return m_layoutStretch;
    }

    bool BoxLayout::isLayoutStretchValid()
    {
        if (!m_layoutStretch.empty())
        {
            if (!std::equal(m_layoutStretch.begin() + 1, m_layoutStretch.end(), m_layoutStretch.begin()))
            {
                if (m_layoutStretch.size() == m_widgets.size())
                {
                    return true;
                }
            }
        }
        return false;
    }
}