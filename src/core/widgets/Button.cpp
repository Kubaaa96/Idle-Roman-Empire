#include "Button.h"

namespace ire::core::widgets
{
	Button::Button()
	{
		m_type = "Button";
	}

	std::unique_ptr<Button> Button::create(const std::string& text)
	{
		auto widget = std::make_unique<Button>();
		// Setting up text on Button in future
		return widget;
	}
	void Button::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
	}
	std::unique_ptr<Widget> Button::clone() const
	{
		return std::unique_ptr<Widget>();
	}
	void Button::draw(sf::RenderTarget& window) const
	{
		// temp for testing 
		sf::RectangleShape rectWidget;
		rectWidget.setPosition(m_position);
		rectWidget.setSize(m_size);
		rectWidget.setFillColor(sf::Color::Red);
		window.draw(rectWidget);
	}
}
