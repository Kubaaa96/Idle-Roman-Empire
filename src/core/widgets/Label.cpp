#include "Label.h"

namespace ire::core::widgets
{
	WidgetType const Label::m_type = WidgetType::create<Label>("Label");


	Label::Label()
	{
	}
	std::unique_ptr<Label> Label::create(const std::string& text)
	{
		auto widget = std::make_unique<Label>();

		return widget;
	}
	void Label::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
	}
	void Label::draw(sf::RenderTarget& target) const
	{
		sf::RectangleShape rectWidget;
		rectWidget.setPosition(m_position);
		rectWidget.setSize(m_size);
		rectWidget.setFillColor(sf::Color::Green);
		target.draw(rectWidget);
	}
}
