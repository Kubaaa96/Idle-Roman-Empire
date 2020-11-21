#include "Button.h"

namespace ire::core::gui
{

	WidgetType const Button::m_type = WidgetType::create<Button>("Button");

	Button::Button()
	{
		m_rectangleShape.setFillColor(sf::Color::Red);
		detail::EagerResource<sf::Font> rs("times.ttf");
		m_text.setFont(*rs);
		m_text.setCharacterSize(15);
		m_text.setFillColor(sf::Color::Black);
	}

	std::unique_ptr<Button> Button::create(const std::string& text)
	{
		auto widget = std::make_unique<Button>();
		// Setting up text on Button in future
		widget->setTextString(text);
		return widget;
	}

	void Button::draw(sf::RenderTarget& target)
	{
		target.draw(m_text);
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
		m_text.setString(m_textString);
		m_rectangleShape.setSize(m_size);

		m_rectangleShape.setPosition(m_position);
		
	}

	void Button::setTextString(const std::string& string)
	{
		m_textString = string;
	}

	sf::String Button::getTextString()
	{
		return m_textString;
	}
}
