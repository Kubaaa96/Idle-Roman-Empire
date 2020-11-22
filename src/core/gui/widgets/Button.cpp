#include "Button.h"

namespace ire::core::gui
{

	WidgetType const Button::m_type = WidgetType::create<Button>("Button");

	Button::Button()
	{
		m_rectangleShape.setFillColor(sf::Color::Red);

		m_text.setFont(*rs);
		// TODO adjusting Size based on position and size of Button
		m_text.setCharacterSize(30);
		m_text.setStyle(sf::Text::Bold);
		m_text.setFillColor(sf::Color::White);
	}

	std::unique_ptr<Button> Button::create(const std::string& text)
	{
		auto widget = std::make_unique<Button>();
		widget->setTextString(text);
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
		target.draw(m_text);
	}
	void Button::updateWidget()
	{
		m_text.setString(m_textString);
		auto textWidth = m_text.getLocalBounds().width;
		auto textHeight = m_text.getLocalBounds().height;

		m_text.setPosition(m_position.x + (m_size.x / 2  - textWidth / 2),
			m_position.y + (m_size.y / 2 - textHeight / 2));

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
