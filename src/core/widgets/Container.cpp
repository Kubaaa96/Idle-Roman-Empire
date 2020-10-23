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

	void Container::add( std::unique_ptr<Widget> widgetPtr)
	{
		widgetPtr->setParent(this);
		m_widgets.push_back(std::move(widgetPtr));
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