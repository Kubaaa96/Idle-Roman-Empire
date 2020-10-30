#include "Button.h"

namespace ire::core::widgets
{

	WidgetType const Button::m_type = WidgetType::create<Button>("Button");

	Button::Button()
	{
		m_rectangleShape.setFillColor(sf::Color::Red);
	}

	std::unique_ptr<Button> Button::create(const std::string& text)
	{
		auto widget = std::make_unique<Button>();
		// Setting up text on Button in future
		return widget;
	}

	void Button::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
	}
	void Button::updateCurrentWidget()
	{
		const auto size = getSize();
		m_rectangleShape.setSize(m_size);

		const auto position = getPosition();
		m_rectangleShape.setPosition(m_position);
		
	}
}
