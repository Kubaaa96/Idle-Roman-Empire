#include "EditBox.h"

namespace ire::core::widgets
{
	WidgetType const EditBox::m_type = WidgetType::create<EditBox>("Edit Box");

	EditBox::EditBox()
	{
	}

	std::unique_ptr<EditBox> EditBox::create(const std::string& text)
	{
		auto widget = std::make_unique<EditBox>();
		// Setting up text on Button in future
		return widget;
	}
	void EditBox::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
	}
	void EditBox::draw(sf::RenderTarget& window) const
	{
		sf::RectangleShape rectWidget;
		rectWidget.setPosition(m_position);
		rectWidget.setSize(m_size);
		rectWidget.setFillColor(sf::Color::Cyan);
		window.draw(rectWidget);
	}
}