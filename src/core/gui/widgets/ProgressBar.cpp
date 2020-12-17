#include "ProgressBar.h"
#include <iostream>

namespace ire::core::gui
{
    WidgetType const ProgressBar::m_type = WidgetType::create<ProgressBar>("ProgressBar");

    ProgressBar::ProgressBar()
	{
		m_rectangleShape.setFillColor(sf::Color::Blue);
		m_progressShape.setFillColor(sf::Color::Green);

		m_font = ResourceManager::instance().get<sf::Font>("resource/RomanSD.ttf");
		m_textMain.setFont(*m_font);
		setCharacterSize(25);
		setTextStyle(sf::Text::Bold);
		setTextFillColor(sf::Color::Black);
		if (m_fillDirection == FillDirection::RightToLeft)
		{
			invertBarsColors();
		}
		updateWidget();
	}

	std::unique_ptr<ProgressBar> ProgressBar::create(const std::string& text)
	{
		auto widget = std::make_unique<ProgressBar>();

		return widget;
	}

	void ProgressBar::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
		target.draw(m_progressShape);
		target.draw(m_textMain);
	}

	void ProgressBar::updateWidget()
	{
		updateTextString();
		updateTextPosition();

		m_rectangleShape.setSize(m_size);
		m_rectangleShape.setPosition(m_position);

		updateFillDirection();
	}
	void ProgressBar::setMinimum(unsigned int minimum)
	{
		if (m_minimum != minimum)
		{
			m_minimum = minimum;
		}
	}
	const unsigned int ProgressBar::getMinimum() const
	{
		return m_minimum;
	}
	void ProgressBar::setMaximum(unsigned int maximum)
	{
		if (m_maximum != maximum)
		{
			m_maximum = maximum;
		}
	}
	const unsigned int ProgressBar::getMaximum() const
	{
		return m_maximum;
	}
	void ProgressBar::setValue(unsigned int value)
	{
		if (m_value != value && m_value - m_minimum > m_maximum - m_minimum)
		{
			m_value = value;
		}
	}
	const unsigned int ProgressBar::getValue() const
	{
		return m_value;
	}
	void ProgressBar::setTextString(std::string& text)
	{
		if (m_textString != text)
		{
			m_textString = text;
		}
	}
	const std::string ProgressBar::getTextString() const
	{
		return m_textString;
	}
	void ProgressBar::setTextSize(unsigned int textSize)
	{
		if (m_textSize != textSize)
		{
			m_textSize = textSize;
		}
	}
	const unsigned int ProgressBar::getTextSize() const
	{
		return m_textSize;
	}
	void ProgressBar::setTextFillColor(sf::Color textColor)
	{
		if (textColor != getTextFillColor())
		{
			m_textMain.setFillColor(textColor);
		}
	}
	const sf::Color ProgressBar::getTextFillColor() const
	{
		return m_textMain.getFillColor();
	}
	void ProgressBar::setTextStyle(sf::Uint32 textStyle)
	{
		if (textStyle != m_textMain.getStyle())
		{
			m_textMain.setStyle(textStyle);
		}
	}
	const sf::Uint32 ProgressBar::getTextStyle() const
	{
		return m_textMain.getStyle();
	}
	void ProgressBar::setFillDirection(FillDirection fillDirection)
	{
		if (m_fillDirection != fillDirection)
		{
			m_fillDirection = fillDirection;
		}
	}
	const ProgressBar::FillDirection ProgressBar::getFillDirection() const
	{
		return m_fillDirection;
	}

	void ProgressBar::setCharacterSize(unsigned int characterSize)
	{
		if (characterSize != m_textMain.getCharacterSize())
		{
			m_textMain.setCharacterSize(characterSize);
		}
	}

	const unsigned int ProgressBar::getCharacterSize() const
	{
		return m_textMain.getCharacterSize();
	}

	void ProgressBar::onEvent(EventRoot& sender, KeyDownEvent& ev)
	{
		switch (ev.key)
		{
		case sf::Keyboard::Left:
			std::cout << "Left\n";
			if (m_value > m_minimum)
			{
				--m_value;
			}
			break;
		case sf::Keyboard::Right:
			std::cout << "Right\n";
			if (m_value < m_maximum)
			{
				++m_value;
			}
			break;
		default:
			break;
		}
		ev.handled = true;
		updateWidget();
		onKeyClicked(ev);
	}

	void ProgressBar::onKeyClicked(KeyDownEvent& ev)
	{
		KeyPressedEvent keyClickedEv{};
		keyClickedEv.timestamp = ev.timestamp;
		keyClickedEv.key = ev.key;
		keyClickedEv.alt = ev.alt;
		keyClickedEv.control = ev.control;
		keyClickedEv.shift = ev.control;
		keyClickedEv.system = ev.system;
		emitEvent<KeyPressedEvent>(keyClickedEv);
	}

	float ProgressBar::calculatedPercent()
	{
		if (m_value - m_minimum > m_maximum - m_minimum)
		{
			throw std::runtime_error("Value is not beetween minimum and maximum");
		}
		return static_cast<float>(m_value - m_minimum) / static_cast<float>(m_maximum - m_minimum);

	}

	void ProgressBar::updateTextPosition()
	{
		auto textWidth = m_textMain.getLocalBounds().width;
		auto textHeight = m_textMain.getLocalBounds().height;
		auto xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
		auto yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
		m_textMain.setPosition(xPosition, yPosition);
	}

	void ProgressBar::updateTextString()
	{
		int percent = calculatedPercent() * 100;
		m_textMain.setString(std::to_string(percent) + "%");
	}

	void ProgressBar::updateFillDirection()
	{
		switch (m_fillDirection)
		{
		case FillDirection::LeftToRight:
			m_progressShape.setSize({ m_size.x * calculatedPercent(), m_size.y });
			m_progressShape.setPosition(m_position);
			break;
		case FillDirection::RightToLeft:
			m_progressShape.setSize({ m_size.x * (1 - calculatedPercent()), m_size.y });
			m_progressShape.setPosition(m_position);
			break;
		case FillDirection::TopToBottom:

			break;
		case FillDirection::BottomToTop:

			break;
		default:
			break;
		}
	}

	void ProgressBar::invertBarsColors()
	{
		auto progressBarColor = m_progressShape.getFillColor();
		m_progressShape.setFillColor(m_rectangleShape.getFillColor());
		m_rectangleShape.setFillColor(progressBarColor);
	}

}