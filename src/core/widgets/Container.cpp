#include "Container.h"

#include <algorithm>

namespace ire::core::widgets
{
	Container::Container()
	{
		m_containerWidget = true;
	}
	void widgets::Container::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
	}

	sf::Vector2f Container::getInnerSize() const
	{
		return getSize();
	}

	const std::vector<std::unique_ptr<Widget>>& Container::getWidgets() const
	{
		return m_widgets;
	}

	void Container::add( std::unique_ptr<Widget> widgetPtr, const std::string& widgetName)
	{
		if (!m_widgets.empty())
		{
			for (std::size_t i = 0; i < m_widgets.size(); ++i)
			{
				if (compareWithWidgetNameAt(i, widgetName))
				{
					// TODO add some debug logger information later
					return;
				}
			}
		}
		widgetPtr->setParent(this);
		widgetPtr->setWidgetName(widgetName);
		m_widgets.push_back(std::move(widgetPtr));
	}

	bool Container::remove(const std::string& widgetName)
	{
		if (!m_widgets.empty())
		{
			for (std::size_t i = 0; i < m_widgets.size(); ++i)
			{
				if (compareWithWidgetNameAt(i, widgetName))
				{
					
					auto it = m_widgets.begin() + i;
					m_widgets.erase(it);
					return true;
				}
			}
		}

		return false;
	}

	Widget* Container::get(int index) 
	{
		return m_widgets.at(index).get();
	}

	Widget* Container::get(const std::string name)
	{
		for (std::size_t i = 0; i < m_widgets.size(); ++i)
		{
			if (compareWithWidgetNameAt(i, name))
			{			
				return m_widgets.at(i).get();
			}		
		}
		return nullptr;
	}

	void Container::draw(sf::RenderTarget& window) const
	{
		// Check if widget is visible after adding that

		for (const auto& widget : m_widgets)
		{
			widget->draw(window);
		}
	}
	bool Container::compareWithWidgetNameAt(std::size_t index, const std::string& name)
	{
		return m_widgets[index].get()->getWidgetName() == name;
	}
}
