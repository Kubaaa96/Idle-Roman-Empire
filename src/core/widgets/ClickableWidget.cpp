#include "ClickableWidget.h"
#include "WidgetType.h"

namespace ire::core::widgets
{
	WidgetType const ClickableWidget::m_type = WidgetType::create<ClickableWidget>("ClickableWidget");

	ClickableWidget::ClickableWidget()
	{
	}

	void ClickableWidget::setSize(const sf::Vector2f& size, bool updateWidget)
	{
		Widget::setSize(size);
		if(updateWidget)
			updateCurrentWidget();
	}
	void ClickableWidget::setPosition(const sf::Vector2f& position, bool updateWidget)
	{
		Widget::setPosition(position);
		if (updateWidget)
			updateCurrentWidget();
	}
	void ClickableWidget::draw(sf::RenderTarget& target)
	{
	}
}
