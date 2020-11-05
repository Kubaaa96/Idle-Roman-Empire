#include "ClickableWidget.h"
#include "WidgetType.h"

#include <iostream>

namespace ire::core::gui
{
	WidgetType const ClickableWidget::m_type = WidgetType::create<ClickableWidget>("ClickableWidget");

	ClickableWidget::ClickableWidget()
	{
	}

	void ClickableWidget::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
		updateWidget();
	}

	void ClickableWidget::setPosition(const sf::Vector2f& position)
	{
		Widget::setPosition(position);
		updateWidget();
	}

	void ClickableWidget::draw(sf::RenderTarget& target)
	{
	}

	void ClickableWidget::onEvent(EventRoot& sender, MouseButtonDownEvent& ev)
	{
		std::cout << "Mouse down detected. MouseButtonDownEvent on " << m_name << '\n';
	}

	void ClickableWidget::onEvent(EventRoot& sender, MouseButtonUpEvent& ev)
	{
		std::cout << "Mouse down detected. MouseButtonUpEvent on " << m_name << '\n';
	}

	void ClickableWidget::onEvent(EventRoot& sender, MouseMovedEvent& ev)
	{
		std::cout << "Mouse down detected. MouseMovedEvent on " << m_name << '\n';
	}
}
