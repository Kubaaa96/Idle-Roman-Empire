#include "ProgressBar.h"
#include <iostream>

namespace ire::core::gui
{
	WidgetType const ProgressBar::m_type = WidgetType::create<ProgressBar>("ProgressBar");

	ProgressBar::ProgressBar() 
	{
		setBackgroundFillColor(sf::Color::Blue);
		setProgressFillColor(sf::Color::Green);

		setMaximumVisibility(true);

		setMinimumVisibility(true);
		
		setValueTextCharacterSize(25);

		setPercentTextCharacterSize(25);
		setPercentVisibility(true);

		setMainTextCharacterSize(25);

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
		if (m_mainText.isVisible())
		{
			target.draw(m_mainText);
		}
		if (m_maximumText.isVisible())
		{
			target.draw(m_maximumText);
		}
		if (m_minimumText.isVisible())
		{
			target.draw(m_minimumText);
		}
		if (m_valueText.isVisible())
		{
			target.draw(m_valueText);
		}
		if (m_percentText.isVisible())
		{
			target.draw(m_percentText);
		}	
	}

	void ProgressBar::updateWidget()
	{
		setTextString(m_minimumText, std::to_string(m_minimum));
		updateMinimumTextPosition();
		
		setTextString(m_maximumText, std::to_string(m_maximum));
		updateMaximumTextPosition();

		int percent = calculatePercent() * 100;
		setTextString(m_percentText, std::to_string(percent) + "%");
		updateTextPosition(m_percentText);

		setTextString(m_valueText, std::to_string(m_value));
		updateTextPosition(m_valueText);

		setTextString(m_mainText, m_mainText.getString());
		updateTextPosition(m_mainText);

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

	const std::string ProgressBar::getMinimumString() const
	{
		return m_minimumText.getString();
	}

	void ProgressBar::setMinimumTextCharacterSize(unsigned int minimumTextCharacterSize)
	{
		setCharacterSize(m_minimumText, minimumTextCharacterSize);
	}

	const unsigned int ProgressBar::getMinimumTextCharacterSize() const
	{
		return getCharacterSize(m_minimumText);
	}

	void ProgressBar::setMinimumTextVerticalAlignment(Text::VerticalAlignment minimumTextVerticalAlignment)
	{
		setVerticalAlignment(m_minimumText, minimumTextVerticalAlignment);
	}

	const std::string ProgressBar::getMinimumTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_minimumText);
	}

	void ProgressBar::setMinimumVisibility(bool isMinimumVisible)
	{
		setVisible(m_minimumText, isMinimumVisible);
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

	void ProgressBar::setMaximumTextCharacterSize(unsigned int maximumTextCharacterSize)
	{
		setCharacterSize(m_maximumText, maximumTextCharacterSize);
	}

	const unsigned int ProgressBar::getMaximumTextCharacterSize() const
	{
		return getCharacterSize(m_maximumText);
	}

	void ProgressBar::setMaximumTextVerticalAlignment(Text::VerticalAlignment maximumTextVerticalAlignment)
	{
		setVerticalAlignment(m_maximumText, maximumTextVerticalAlignment);
	}

	const std::string ProgressBar::getMaximumTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_maximumText);
	}

	void ProgressBar::setMaximumVisibility(bool isMaximumVisible)
	{
		setVisible(m_maximumText, isMaximumVisible);
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

	void ProgressBar::setValueTextCharacterSize(unsigned int valueTextCharacterSize)
	{
		setCharacterSize(m_valueText, valueTextCharacterSize);
	}

	const unsigned int ProgressBar::getValueTextCharacterSize() const
	{
		return getCharacterSize(m_valueText);
	}

	void ProgressBar::setValueTextVerticalAlignment(Text::VerticalAlignment valueTextVerticalAlignment)
	{
		setVerticalAlignment(m_valueText, valueTextVerticalAlignment);
	}

	const std::string ProgressBar::getValueTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_valueText);;
	}

	void ProgressBar::setValueVisibility(bool isValueVisible)
	{
		setVisible(m_valueText, isValueVisible);
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

	const float ProgressBar::getPercent() const
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

	void ProgressBar::setPercentTextVerticalAlignment(Text::VerticalAlignment percentTextVerticalAlignment)
	{
		setVerticalAlignment(m_percentText, percentTextVerticalAlignment);
	}

	const std::string ProgressBar::getPercentTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_percentText);
	}

	void ProgressBar::setPercentVisibility(bool isPercentVisible)
	{
		setVisible(m_percentText, isPercentVisible);
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
		m_mainText.setString(string);
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

	void ProgressBar::setMainTextVerticalAlignment(Text::VerticalAlignment mainTextVerticalAlignment)
	{
		setVerticalAlignment(m_mainText, mainTextVerticalAlignment);
	}

	const std::string ProgressBar::getMainTextVerticalAlignmentString() const
	{
		return getVerticalAlignmentString(m_mainText);
	}

	void ProgressBar::setMainVisibility(bool isMainVisible)
	{
		setVisible(m_mainText, isMainVisible);
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

	void ProgressBar::updateMaximumTextPosition()
	{
		switch (m_fillDirection)
		{
		case FillDirection::LeftToRight:
			m_maximumText.setHorizontalAlign(Text::HorizontalAlignment::Right);
			break;
		case FillDirection::RightToLeft:
			m_maximumText.setHorizontalAlign(Text::HorizontalAlignment::Left);
			break;
		case FillDirection::BottomToTop:
			m_maximumText.setHorizontalAlign(Text::HorizontalAlignment::Center);
			m_maximumText.setVerticalAlign(Text::VerticalAlignment::Top);
			break;
		case FillDirection::TopToBottom:
			m_maximumText.setHorizontalAlign(Text::HorizontalAlignment::Center);
			m_maximumText.setVerticalAlign(Text::VerticalAlignment::Bottom);
			break;
		default:
			break;
		}
		updateTextPosition(m_maximumText);
	}

	void ProgressBar::updateMinimumTextPosition()
	{
		switch (m_fillDirection)
		{
		case FillDirection::LeftToRight:
			m_minimumText.setHorizontalAlign(Text::HorizontalAlignment::Left);
			break;
		case FillDirection::RightToLeft:
			m_minimumText.setHorizontalAlign(Text::HorizontalAlignment::Right);
			break;
		case FillDirection::BottomToTop:
			m_minimumText.setHorizontalAlign(Text::HorizontalAlignment::Center);
			m_minimumText.setVerticalAlign(Text::VerticalAlignment::Bottom);
			break;
		case FillDirection::TopToBottom:
			m_minimumText.setHorizontalAlign(Text::HorizontalAlignment::Center);
			m_minimumText.setVerticalAlign(Text::VerticalAlignment::Top);
			break;
		default:
			break;
		}
		updateTextPosition(m_minimumText);
	} 

	void ProgressBar::updateTextPosition(Text& text)
	{
		text.setTextPosition(m_position, m_size);

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
		if (text.getString() != string)
		{
			text.setString(string);
		}
	}

	const std::string ProgressBar::getTextString(Text text) const
	{
		return text.getString();
	}

	void ProgressBar::setCharacterSize(Text& text, unsigned int characterSize)
	{
		if (text.getCharacterSize() != characterSize)
		{
			text.setCharacterSize(characterSize);
		}
	}

	const unsigned int ProgressBar::getCharacterSize(Text text) const
	{
		return text.getCharacterSize();
	}

	void ProgressBar::setVerticalAlignment(Text& text, Text::VerticalAlignment verticalAlignment)
	{
		if (text.getVerticalAlign() != verticalAlignment)
		{
			text.setVerticalAlign(verticalAlignment);
		}
	}

	const std::string ProgressBar::getVerticalAlignmentString(Text text) const
	{
		switch (text.getVerticalAlign())
		{
		case Text::VerticalAlignment::Bottom:
			return "Bottom";
		case Text::VerticalAlignment::Center:
			return "Center";
		case Text::VerticalAlignment::Top:
			return "Top";
		default:
			break;
		}
	}

	void ProgressBar::setVisible(Text& text, bool isVisible)
	{
		if (text.isVisible() != isVisible)
		{
			text.setVisible(isVisible);
		}
	}

	const bool ProgressBar::isVisible(Text text) const
	{
		return text.isVisible();
	}

	void ProgressBar::setFillColor(Text& text, sf::Color color)
	{
		if (text.getFillColor() != color)
		{
			text.setFillColor(color);
		}
	}

	const sf::Color ProgressBar::getFillColor(Text text) const
	{
		return text.getFillColor();
	}
}