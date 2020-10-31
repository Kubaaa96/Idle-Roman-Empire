#include "BoxLayout.h"

#include <numeric>
#include <algorithm>
#include <functional>


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
    void BoxLayout::setPosition(const sf::Vector2f& position)
    {
        Container::setPosition(position);
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
        updateWidgets();
        return m_spaces;
    }

    void BoxLayout::setLayoutStretch(std::vector<float> relativeSizes)
    {
        // Check if number of items in initializer_list is the same as m_widgets.size()
        if (relativeSizes.size() != m_widgets.size())
        {
            throw ("Size of list and widget vector is different. Need to be the same");
            return;
        }
        m_layoutStretch = relativeSizes;
        m_sumOfLayoutStretches = std::accumulate(m_layoutStretch.begin(), m_layoutStretch.end(), 0.f);

        updateWidgets();
    }

    const std::vector<float>& BoxLayout::getLayoutStretch() const
    {
        return m_layoutStretch;
    }

    bool BoxLayout::isLayoutStretchValid()
    {
        if (!m_layoutStretch.empty()
            && !std::all_of(m_layoutStretch.begin() + 1, m_layoutStretch.end(), std::bind(std::equal_to<float>(),
                std::placeholders::_1, m_layoutStretch.front()))
            && m_layoutStretch.size() == m_widgets.size())
        {
            return true;
        }
        return false;
    }
}