#include "ClickableWidget.h"
#include "WidgetType.h"

namespace ire::core::widgets
{

	WidgetType ClickableWidget::m_type = WidgetType::create<ClickableWidget>("ClickableWidget");

	ClickableWidget::ClickableWidget()
	{
		
	}
	std::unique_ptr<ClickableWidget> ClickableWidget::create(sf::Vector2f size)
	{
		auto widget = std::make_unique<ClickableWidget>();
		widget->setSize(size.x, size.y);
		return widget;
	}
	std::unique_ptr<Widget> ClickableWidget::clone() const
	{
		return std::unique_ptr<Widget>();
	}
	void ClickableWidget::draw(sf::RenderTarget& window) const
	{
	}
}