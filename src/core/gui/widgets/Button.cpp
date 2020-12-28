#include "Button.h"
#include <iostream>

namespace ire::core::gui
{

	WidgetType const Button::m_type = WidgetType::create<Button>("Button");

	Button::Button()
	{
		m_rectangleShape.setFillColor(sf::Color::Red);
		
		setTextOutlineThickness(0);
		setCharacterSize(30);
		setAlignment(Text::VerticalAlignment::Center, Text::HorizontalAlignment::Center);
		setTextStyle(sf::Text::Bold);
		setTextFillColor(sf::Color::White);
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
		m_text.setString(m_text.getString());
		updateTextPosition();

		m_rectangleShape.setSize(m_size);
		m_rectangleShape.setPosition(m_position);

	}

	void Button::setTextString(const std::string& string)
	{
		if (m_text.getString() != string)
		{
			m_text.setString(string);
		}
	}

	sf::String Button::getTextString()
	{
		return m_text.getString();
	}

	void Button::setCharacterSize(const unsigned int characterSize)
	{
		m_text.setCharacterSize(characterSize);
		updateWidget();
	}

	const unsigned int Button::getCharacterSize() const
	{
		return m_text.getCharacterSize();
	}

	void Button::setTextStyle(const sf::Uint32 style)
	{
		m_text.setStyle(style);
	}

	const sf::Uint32 Button::getTextStyle() const
	{
		return m_text.getStyle();
	}

	void Button::setTextFillColor(const sf::Color textFillColor)
	{
		m_text.setFillColor(textFillColor);
	}

	const sf::Color Button::getTextFillColor() const
	{
		return m_text.getFillColor();
	}

	void Button::setTextOutlineColor(const sf::Color textOutlineColor)
	{
		if (m_text.getOutlineColor() != textOutlineColor)
		{
			m_text.setOutlineColor(textOutlineColor);
		}
	}

	const sf::Color Button::getTextOutlineColor() const
	{
		return m_text.getOutlineColor();
	}

	void Button::setTextOutlineThickness(const float textOutlineThickness)
	{
		if (m_text.getOutlineThickness() != textOutlineThickness)
		{
			m_text.setOutlineThickness(textOutlineThickness);
		}
	}

	const float Button::getTextOutlineThickness() const
	{
		return m_text.getOutlineThickness();
	}

	void Button::setVAlignment(Text::VerticalAlignment vAlign)
	{
		if (m_text.getVerticalAlign() != vAlign)
		{
			m_text.setVerticalAlign(vAlign);
		}
	}

	const Text::VerticalAlignment Button::getVAlignment() const
	{
		return m_text.getVerticalAlign();
	}

	void Button::setHAlignment(Text::HorizontalAlignment hAlign)
	{
		if (m_text.getHorizontalAlign() != hAlign)
		{
			m_text.setHorizontalAlign(hAlign);
		}
	}

	const Text::HorizontalAlignment Button::getHAlignment() const
	{
		return m_text.getHorizontalAlign();
	}

	void Button::setAlignment(Text::VerticalAlignment vAlign, Text::HorizontalAlignment hAlign)
	{
	    setVAlignment(vAlign);
	    setHAlignment(hAlign);
	}
	void Button::updateTextPosition()
	{
		m_text.setTextPosition(m_position, m_size);
	}
}