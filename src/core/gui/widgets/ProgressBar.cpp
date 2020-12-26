#include "ProgressBar.h"
#include <iostream>
#include "..\Text.h"

namespace ire::core::gui
{
	WidgetType const ProgressBar::m_type = WidgetType::create<ProgressBar>("ProgressBar");

	ProgressBar::ProgressBar() 
	{
		m_font = ResourceManager::instance().get<sf::Font>("resource/RomanSD.ttf");

		setBackgroundFillColor(sf::Color::Blue);
		setProgressFillColor(sf::Color::Green);

		m_maximumText.m_text.setFont(*m_font);
		setMaximumVisibility(true);

		m_minimumText.m_text.setFont(*m_font);
		setMinimumVisibility(true);
		
		m_valueText.m_text.setFont(*m_font);
		setValueTextCharacterSize(25);

		m_percentText.m_text.setFont(*m_font);
		setPercentTextCharacterSize(25);
		setPercentVisibility(true);

		m_mainText.m_text.setFont(*m_font);
		//setMainTextCharacterSize(25);

		if (m_fillDirection == FillDirection::RightToLeft || m_fillDirection == FillDirection::BottomToTop)
		{
			invertBarsColors();
		}
		updateWidget();
	}

	std::unique_ptr<ProgressBar> ProgressBar::create(const std::string& text)
	{
		auto widget = std::make_unique<ProgressBar>();
		widget->setMainTextString(text);
		return widget;
	}

	void ProgressBar::draw(sf::RenderTarget& target)
	{
		target.draw(m_backgroundShape);
		target.draw(m_progressShape);
		if (m_mainText.m_isTextVisible)
		{
			target.draw(m_mainText.m_text);
		}
		if (m_maximumText.m_isTextVisible)
		{
			target.draw(m_maximumText.m_text);
		}
		if (m_minimumText.m_isTextVisible)
		{
			target.draw(m_minimumText.m_text);
		}
		if (m_valueText.m_isTextVisible)
		{
			target.draw(m_valueText.m_text);
		}
		if (m_percentText.m_isTextVisible)
		{
			target.draw(m_percentText.m_text);
		}	
	}

	void ProgressBar::updateWidget()
	{
		updateMinimumTextString();
		updateMinimumTextPosition();

		updateMaximumTextString();
		updateMaximumTextPosition();

		updatePercentTextString();
		updatePercentTextPosition();

		updateValueTextString();
		updateValueTextPosition();

		updateMainTextString();
		updateMainTextPosition();

		m_backgroundShape.setSize(m_size);
		m_backgroundShape.setPosition(m_position);

		updateFillDirection();
	}
	void ProgressBar::setMinimum(uint64_t minimum)
	{
		if (m_minimum != minimum)
		{
			m_minimum = minimum;
		}
	}

	const uint64_t ProgressBar::getMinimum() const
	{
		return m_minimum;
	}

	void ProgressBar::setMinimumTextString(std::string string)
	{
		setTextString(m_minimumText, string);
	}

	const std::string ProgressBar::getMinimumString() const
	{
		return m_minimumText.m_textString;
	}

	void ProgressBar::setMinimumTextCharacterSize(unsigned int minimumTextCharacterSize)
	{
		setCharacterSize(m_minimumText, minimumTextCharacterSize);
	}

	const unsigned int ProgressBar::getMinimumTextCharacterSize() const
	{
		return getCharacterSize(m_minimumText);
	}

	void ProgressBar::setMinimumTextVerticalAlignment(VerticalTextAlignment minimumTextVerticalAlignment)
	{
		setVerticalAlignment(m_minimumText, minimumTextVerticalAlignment);
	}

	const std::string ProgressBar::getMinimumTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_minimumText);
	}

	void ProgressBar::setMinimumVisibility(bool isMinimumVisible)
	{
		setVisibility(m_minimumText, isMinimumVisible);
	}

	const bool ProgressBar::isMinimumVisible() const
	{
		return isVisible(m_minimumText);
	}

	void ProgressBar::setMinimumTextFillColor(sf::Color minimumTextFillColor)
	{
		setFillColor(m_minimumText, minimumTextFillColor);
	}

	const sf::Color ProgressBar::getMinimumTextFillColor() const
	{
		return getFillColor(m_minimumText);
	}

	void ProgressBar::setMaximum(uint64_t maximum)
	{
		if (m_maximum != maximum)
		{
			m_maximum = maximum;
		}
	}

	const uint64_t ProgressBar::getMaximum() const
	{
		return m_maximum;
	}

	void ProgressBar::setMaximumTextString(std::string string)
	{
		setTextString(m_maximumText, string);
	}

	void ProgressBar::setMaximumTextCharacterSize(unsigned int maximumTextCharacterSize)
	{
		setCharacterSize(m_maximumText, maximumTextCharacterSize);
	}

	const unsigned int ProgressBar::getMaximumTextCharacterSize() const
	{
		return getCharacterSize(m_maximumText);
	}

	void ProgressBar::setMaximumTextVerticalAlignment(VerticalTextAlignment maximumTextVerticalAlignment)
	{
		setVerticalAlignment(m_maximumText, maximumTextVerticalAlignment);
	}

	const std::string ProgressBar::getMaximumTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_maximumText);
	}

	void ProgressBar::setMaximumVisibility(bool isMaximumVisible)
	{
		setVisibility(m_maximumText, isMaximumVisible);
	}

	const bool ProgressBar::isMaximumVisible() const
	{
		return isVisible(m_maximumText);
	}

	void ProgressBar::setMaximumTextFillColor(sf::Color maximumTextFillColor)
	{
		setFillColor(m_maximumText, maximumTextFillColor);
	}

	const sf::Color ProgressBar::getMaximumTextFillColor() const
	{
		return getFillColor(m_maximumText);
	}

	void ProgressBar::setValue(uint64_t value)
	{
		if (m_value != value)
		{
			if (value > m_maximum)
			{
				m_value = m_maximum;
			}
			else if (value < m_minimum)
			{
				m_value = m_minimum;
			}
			else
			{
				m_value = value;
			}
			ProgressBarValueChanged ev;
			ev.value = m_value;
			emitEvent(ev);
		}

		updateWidget();
	}

	const uint64_t ProgressBar::getValue() const
	{
		return m_value;
	}

	void ProgressBar::setValueTextString(std::string string)
	{
		setTextString(m_valueText, string);
	}

	void ProgressBar::setValueTextCharacterSize(unsigned int valueTextCharacterSize)
	{
		setCharacterSize(m_valueText, valueTextCharacterSize);
	}

	const unsigned int ProgressBar::getValueTextCharacterSize() const
	{
		return getCharacterSize(m_valueText);
	}

	void ProgressBar::setValueTextVerticalAlignment(VerticalTextAlignment valueTextVerticalAlignment)
	{
		setVerticalAlignment(m_valueText, valueTextVerticalAlignment);
	}

	const std::string ProgressBar::getValueTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_valueText);;
	}

	void ProgressBar::setValueVisibility(bool isValueVisible)
	{
		setVisibility(m_valueText, isValueVisible);
	}

	const bool ProgressBar::isValueVisible() const
	{
		return isVisible(m_valueText);
	}

	void ProgressBar::setValueTextFillColor(sf::Color valueTextFillColor)
	{
		setFillColor(m_valueText, valueTextFillColor);
	}

	const sf::Color ProgressBar::getValueTextFillColor() const
	{
		return getFillColor(m_valueText);
	}

	void ProgressBar::setPercentTextString(std::string percentTextString)
	{
		setTextString(m_percentText, percentTextString + "%");
	}

	const uint64_t ProgressBar::getPercent() const
	{
		return calculatePercent();
	}

	void ProgressBar::setPercentTextCharacterSize(unsigned int percentTextCharacterSize)
	{
		setCharacterSize(m_percentText, percentTextCharacterSize);
	}

	const unsigned int ProgressBar::getPercentTextCharacterSize() const
	{
		return getCharacterSize(m_percentText);
	}

	void ProgressBar::setPercentTextVerticalAlignment(VerticalTextAlignment percentTextVerticalAlignment)
	{
		setVerticalAlignment(m_percentText, percentTextVerticalAlignment);
	}

	const std::string ProgressBar::getPercentTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_percentText);
	}

	void ProgressBar::setPercentVisibility(bool isPercentVisible)
	{
		setVisibility(m_percentText, isPercentVisible);
	}

	const bool ProgressBar::isPercentVisible() const
	{
		return isVisible(m_percentText);
	}

	void ProgressBar::setPercentTextFillColor(sf::Color percentTextFillColor)
	{
		setFillColor(m_percentText, percentTextFillColor);
	}

	const sf::Color ProgressBar::getPercentTextFillColor() const
	{
		return getFillColor(m_percentText);
	}

	void ProgressBar::setMainTextString(std::string string)
	{
		setTextString(m_mainText, string);
	}

	const std::string ProgressBar::getMainString() const
	{
		return getTextString(m_mainText);
	}

	void ProgressBar::setMainTextCharacterSize(unsigned int mainTextCharacterSize)
	{
		setCharacterSize(m_mainText, mainTextCharacterSize);
	}

	const unsigned int ProgressBar::getMainTextCharacterSize() const
	{
		return getCharacterSize(m_mainText);
	}

	void ProgressBar::setMainTextVerticalAlignment(VerticalTextAlignment mainTextVerticalAlignment)
	{
		setVerticalAlignment(m_mainText, mainTextVerticalAlignment);
	}

	const std::string ProgressBar::getMainTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_mainText);
	}

	void ProgressBar::setMainVisibility(bool isMainVisible)
	{
		setVisibility(m_mainText, isMainVisible);
	}

	const bool ProgressBar::isMainVisible() const
	{
		return isVisible(m_mainText);
	}

	void ProgressBar::setMainTextFillColor(sf::Color mainTextFillColor)
	{
		setFillColor(m_mainText, mainTextFillColor);
	}

	const sf::Color ProgressBar::getMainTextFillColor() const
	{
		return getFillColor(m_mainText);
	}

	void ProgressBar::setProgressFillColor(sf::Color barFillColor)
	{
		if (m_progressFillColor != barFillColor)
		{
			m_progressFillColor = barFillColor;
			m_progressShape.setFillColor(barFillColor);
		}
	}

	const sf::Color ProgressBar::getProgressFillColor() const
	{
		return m_progressFillColor;
	}

	void ProgressBar::setBackgroundFillColor(sf::Color backgroundFillColor)
	{
		if (m_backgroundFillColor != backgroundFillColor)
		{
			m_backgroundFillColor = backgroundFillColor;
			m_backgroundShape.setFillColor(backgroundFillColor);
		}
	}

	const sf::Color ProgressBar::getBackgroundFillColor() const
	{
		return m_backgroundFillColor;
	}

	void ProgressBar::setFillDirection(FillDirection fillDirection)
	{
		if (m_fillDirection != fillDirection)
		{
			m_fillDirection = fillDirection;
			if (m_fillDirection == FillDirection::RightToLeft || m_fillDirection == FillDirection::BottomToTop)
			{
				invertBarsColors();
			}
		}
	}

	const ProgressBar::FillDirection ProgressBar::getFillDirection() const
	{
		return m_fillDirection;
	}

	const float ProgressBar::calculatePercent() const
	{
		return static_cast<float>(m_value - m_minimum) / static_cast<float>(m_maximum - m_minimum);
	}

	void ProgressBar::updateMainTextPosition()
	{
		auto textWidth = m_mainText.m_text.getLocalBounds().width;
		auto textHeight = m_mainText.m_text.getLocalBounds().height;
		auto xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
		auto yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
		updateTextPosition(m_mainText, xPosition, yPosition);
	}

	void ProgressBar::updateMaximumTextPosition()
	{
		auto letterSpacing{ m_maximumText.m_text.getLetterSpacing() };
		auto textWidth = m_maximumText.m_text.getLocalBounds().width;
		auto textHeight = m_minimumText.m_text.getLocalBounds().height;
		auto xPosition = 0.f;
		auto yPosition = 0.f;
		switch (m_fillDirection)
		{
		case FillDirection::LeftToRight:
			xPosition = m_position.x + m_size.x - textWidth - letterSpacing;
			break;
		case FillDirection::RightToLeft:
			xPosition = m_position.x + letterSpacing;
			break;
		case FillDirection::BottomToTop:
			xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
			yPosition = m_position.y + letterSpacing;
			break;
		case FillDirection::TopToBottom:
			xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
			yPosition = m_position.y + m_size.y - textHeight - letterSpacing * 10;
			break;
		default:
			break;
		}
		updateTextPosition(m_maximumText, xPosition, yPosition);
	}

	void ProgressBar::updateMinimumTextPosition()
	{
		auto letterSpacing{ m_minimumText.m_text.getLetterSpacing() };
		auto textWidth = m_minimumText.m_text.getLocalBounds().width;
		auto textHeight = m_minimumText.m_text.getLocalBounds().height;
		auto xPosition = 0.f;
		auto yPosition = 0.f;
		switch (m_fillDirection)
		{
		case FillDirection::LeftToRight:
			xPosition = m_position.x + letterSpacing;
			break;
		case FillDirection::RightToLeft:
			xPosition = m_position.x + m_size.x - textWidth - letterSpacing;
			break;
		case FillDirection::BottomToTop:
			xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
			yPosition = m_position.y + m_size.y - textHeight - letterSpacing * 10;
			break;
		case FillDirection::TopToBottom:
			xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
			yPosition = m_position.y + letterSpacing;
			break;
		default:
			break;
		}
		updateTextPosition(m_minimumText, xPosition, yPosition);
	} 

	void ProgressBar::updateValueTextPosition()
	{
		auto textWidth = m_valueText.m_text.getLocalBounds().width;
		auto textHeight = m_valueText.m_text.getLocalBounds().height;
		auto xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
		auto yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
		updateTextPosition(m_valueText, xPosition, yPosition);
	}

	void ProgressBar::updatePercentTextPosition()
	{
		auto textWidth = m_percentText.m_text.getLocalBounds().width;
		auto textHeight = m_percentText.m_text.getLocalBounds().height;
		auto xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
		auto yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
		updateTextPosition(m_percentText, xPosition, yPosition);
	}

	void ProgressBar::updateTextPosition(Text& text, float xPosition, float yPosition)
	{
		auto textWidth = m_percentText.m_text.getLocalBounds().width;
		auto textHeight = text.m_text.getLocalBounds().height;
		auto letterSpacing{ text.m_text.getLetterSpacing() };
		if (m_fillDirection == FillDirection::LeftToRight || m_fillDirection == FillDirection::RightToLeft)
		{
			switch (text.m_textVerticalAlignement)
			{
			case VerticalTextAlignment::Bottom:
				yPosition = m_position.y + m_size.y - textHeight - letterSpacing;
				break;
			case VerticalTextAlignment::Center:
				yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
				break;
			case VerticalTextAlignment::Top:
				yPosition = m_position.y + letterSpacing;
				break;
			default:
				break;
			}
		}
		text.m_text.setPosition(xPosition, yPosition);
	}

	void ProgressBar::updateMainTextString()
	{
		setMainTextString(m_mainText.m_textString);
	}

	void ProgressBar::updateMaximumTextString()
	{
		setMaximumTextString(std::to_string(m_maximum));
	}

	void ProgressBar::updateMinimumTextString()
	{
		setMinimumTextString(std::to_string(m_minimum));
	}

	void ProgressBar::updateValueTextString()
	{
		setValueTextString(std::to_string(m_value));
	}

	void ProgressBar::updatePercentTextString()
	{
		int percent = calculatePercent() * 100;
		setPercentTextString(std::to_string(percent));
	}

	void ProgressBar::updateFillDirection()
	{
		switch (m_fillDirection)
		{
		case FillDirection::LeftToRight:
			m_progressShape.setSize({ m_size.x * calculatePercent(), m_size.y });
			break;
		case FillDirection::RightToLeft:
			m_progressShape.setSize({ m_size.x * (1 - calculatePercent()), m_size.y });
			break;
		case FillDirection::TopToBottom:
			m_progressShape.setSize({ m_size.x, m_size.y * calculatePercent() });
			break;
		case FillDirection::BottomToTop:
			m_progressShape.setSize({ m_size.x , m_size.y * (1 - calculatePercent() )});
			break;
		default:
			break;
		}
		m_progressShape.setPosition(m_position);
	}

	void ProgressBar::invertBarsColors()
	{
		auto progressBarColor = m_progressShape.getFillColor();
		m_progressShape.setFillColor(m_backgroundShape.getFillColor());
		m_backgroundShape.setFillColor(progressBarColor);
	}

	void ProgressBar::setTextString(Text& text, std::string string)
	{
		if (text.m_textString != string)
		{
			text.m_textString = string;
			text.m_text.setString(string);
		}
	}

	const std::string ProgressBar::getTextString(Text text) const
	{
		return text.m_textString;
	}

	void ProgressBar::setCharacterSize(Text& text, unsigned int characterSize)
	{
		if (text.m_characterSize != characterSize)
		{
			text.m_characterSize = characterSize;
			text.m_text.setCharacterSize(text.m_characterSize);
		}
	}

	const unsigned int ProgressBar::getCharacterSize(Text text) const
	{
		return text.m_characterSize;
	}

	void ProgressBar::setVerticalAlignment(Text& text, VerticalTextAlignment verticalAlignment)
	{
		if (text.m_textVerticalAlignement != verticalAlignment)
		{
			text.m_textVerticalAlignement = verticalAlignment;
		}
	}

	const std::string ProgressBar::getVerticalAlignmentString(Text text) const
	{
		switch (text.m_textVerticalAlignement)
		{
		case VerticalTextAlignment::Bottom:
			return "Bottom";
		case VerticalTextAlignment::Center:
			return "Center";
		case VerticalTextAlignment::Top:
			return "Top";
		default:
			break;
		}
	}

	void ProgressBar::setVisibility(Text& text, bool isVisible)
	{
		if (text.m_isTextVisible != isVisible)
		{
			text.m_isTextVisible = isVisible;
		}
	}

	const bool ProgressBar::isVisible(Text text) const
	{
		return text.m_isTextVisible;
	}

	void ProgressBar::setFillColor(Text& text, sf::Color color)
	{
		if (text.m_textFillColor != color)
		{
			text.m_textFillColor = color;
			text.m_text.setFillColor(color);
		}
	}

	const sf::Color ProgressBar::getFillColor(Text text) const
	{
		return text.m_textFillColor;
	}

	ProgressBar::Text::Text()
	{
		m_text.setFillColor(m_textFillColor);
		m_text.setOutlineColor(sf::Color::White);
		m_text.setOutlineThickness(2);
		m_text.setString(m_textString);
		m_text.setCharacterSize(m_characterSize);
	}
}