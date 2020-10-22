#include "Container.h"

namespace ire::core::widgets
{
	void widgets::Container::setSize(const sf::Vector2f& size)
	{
	}

	const std::vector<std::unique_ptr<Widget>>& Container::getWidgets() const
	{
		return m_widgets;
	}

	void Container::add(const std::unique_ptr<Widget>& widgetPtr, const std::string& widgetName)
	{
		if (widgetPtr->getParent())
		{
			widgetPtr->getParent()->remove(widgetPtr);
		}
		widgetPtr->setParent(this);
		m_widgets.push_back(widgetPtr);
		widgetPtr->setWidgetName(widgetName);
	}

	bool Container::remove(const std::unique_ptr<Widget>& widgetPtr)
	{
		for (std::size_t i = 0; i < m_widgets.size(); ++i)
		{
			if (m_widgets[i] != widgetPtr)
				continue;

			widgetPtr->setParent(nullptr);
			m_widgets.erase(m_widgets.begin() + i);
			return true;
		}

		return false;
	}

	void Container::removeAllWidgets()
	{
		for (const auto& widget : m_widgets)
			widget->setParent(nullptr);
		
		m_widgets.clear();
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