#include "Button.h"

namespace ire::core::gui
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
		if (m_state == State::Armed)
		{
			auto shape = m_rectangleShape;
			shape.move(sf::Vector2f(1.0f, 1.0f));
			shape.setFillColor(shape.getFillColor() + sf::Color(40, 40, 40));
			target.draw(shape);
		}
		else if (m_state == State::Hover)
		{
			auto shape = m_rectangleShape;
			shape.setFillColor(shape.getFillColor() + sf::Color(40, 40, 40));
			target.draw(shape);
		}
		else
		{
			target.draw(m_rectangleShape);
		}
	}
	void Button::updateWidget()
	{
		//const auto size = getSize();
		m_rectangleShape.setSize(m_size);

		//const auto position = getPosition();
		m_rectangleShape.setPosition(m_position);
		
	}
}
