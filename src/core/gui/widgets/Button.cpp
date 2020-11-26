#include "Button.h"
#include <iostream>

namespace ire::core::gui
{

	WidgetType const Button::m_type = WidgetType::create<Button>("Button");

	Button::Button()
	{
		m_rectangleShape.setFillColor(sf::Color::Red);

		m_text.setFont(*m_font);
		setCharacterSize(30);
		setAlignment(VAlign::Center, HAlign::Center);
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
		m_text.setString(m_textString);
		updatePosition();

		m_rectangleShape.setSize(m_size);
		m_rectangleShape.setPosition(m_position);

	}

	void Button::setTextString(const std::string& string)
	{
		if (m_textString != string)
		{
			m_textString = string;
		}
	}

	sf::String Button::getTextString()
	{
		return m_textString;
	}

	void Button::setCharacterSize(const unsigned int characterSize)
	{
		m_text.setCharacterSize(characterSize);
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

	void Button::setVAlignment(VAlign vAlign)
	{
		if (m_vAlign != vAlign)
		{
			m_vAlign = vAlign;
		}
	}

	const VAlign Button::getVAlignment() const
	{
		return m_vAlign;
	}

	void Button::setHAlignment(HAlign hAlign)
	{
		if (m_hAlign != hAlign)
		{
			m_hAlign = hAlign;
		}
	}

	const HAlign Button::getHAlignment() const
	{
		return m_hAlign;
	}

	void Button::setAlignment(VAlign vAlign, HAlign hAlign)
	{
	    setVAlignment(vAlign);
	    setHAlignment(hAlign);
	}
	void Button::updatePosition()
	{
        auto textWidth = m_text.getLocalBounds().width;
        auto textHeight = m_text.getLocalBounds().height;
        auto letterSpacing{ m_text.getLetterSpacing() };
        auto xPosition = m_text.getPosition().x;

        switch (m_vAlign)
        {
	    case VAlign::Left:
            xPosition = m_position.x + letterSpacing;
            break;
        case VAlign::Right:
            xPosition = m_position.x + m_size.x - textWidth - letterSpacing;
            break;
        case VAlign::Center:
            xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
            break;
        default:
            break;
        }
	
		auto yPosition = m_text.getPosition().y;
		switch (m_hAlign)
		{
		case HAlign::Top:
			yPosition = m_position.y + letterSpacing;
			break;
		case HAlign::Bottom:
			yPosition = m_position.y + m_size.y - textHeight - letterSpacing;
			break;
		case HAlign::Center:
			yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
			break;
		default:
			break;
		}
		m_text.setPosition(xPosition, yPosition);
	}
}
