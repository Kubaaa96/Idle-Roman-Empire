#include "Container.h"

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
		widgetPtr->setParent(this);
		widgetPtr->setWidgetName(widgetName);
		m_widgets.push_back(std::move(widgetPtr));
	}

	std::unique_ptr<Widget> &Container::get(int index) 
	{
		return m_widgets.at(index);
	}

	std::unique_ptr<Widget>& Container::get(std::string& name)
	{
		std::size_t indexOfWidget = 0;
		bool isWidgetInVector = false;
		for (std::size_t i = 0; i < m_widgets.size(); ++i)
		{
			if (m_widgets[i].get()->getWidgetName().compare(name) == 0)
			{			
				return m_widgets.at(i);
			}
		}
		return std::unique_ptr<Widget>(nullptr);
	}

	void Container::draw(sf::RenderWindow& window) const
	{
		// Check if widget is visible after adding that

		for (const auto& widget : m_widgets)
		{
			widget->draw(window);
		}
	}
}