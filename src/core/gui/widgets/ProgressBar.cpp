#include "ProgressBar.h"
#include <iostream>

namespace ire::core::gui
{
	WidgetType const ProgressBar::m_type = WidgetType::create<ProgressBar>("ProgressBar");

	ProgressBar::ProgressBar()
	{
		m_font = ResourceManager::instance().get<sf::Font>("resource/RomanSD.ttf");

		m_backgroundShape.setFillColor(m_backgroundFillColor);
		m_progressShape.setFillColor(m_progressFillColor);

		m_maximumText.m_text.setFont(*m_font);

		m_minimumText.m_text.setFont(*m_font);
		
		m_valueText.m_text.setFont(*m_font);

		m_percentText.m_text.setFont(*m_font);
		m_percentText.m_isTextVisible = true;

		m_mainText.m_text.setFont(*m_font);
		m_mainText.m_characterSize = 25;

		if (m_fillDirection == FillDirection::RightToLeft || m_fillDirection == FillDirection::BottomToTop)
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
		updatePercentTextString();
		updatePercentTextPosition();

		m_backgroundShape.setSize(m_size);
		m_backgroundShape.setPosition(m_position);

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

	void ProgressBar::setMinimumTextCharacterSize(unsigned int minimumTextCharacterSize)
	{
		setCharacterSize(m_minimumText, minimumTextCharacterSize);
	}

	const unsigned int ProgressBar::getMinimumTextCharacterSize() const
	{
		return getCharacterSize(m_minimumText);
	}

	void ProgressBar::setMinimumTextVerticalAlighnment(VerticalTextAlignment minimumTextVerticalAlignment)
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

	void ProgressBar::setMaximumTextCharacterSize(unsigned int maximumTextCharacterSize)
	{
		setCharacterSize(m_maximumText, maximumTextCharacterSize);
	}

	const unsigned int ProgressBar::getMaximumTextCharacterSize() const
	{
		return getCharacterSize(m_maximumText);
	}

	void ProgressBar::setMaximumTextVerticalAlighnment(VerticalTextAlignment maximumTextVerticalAlignment)
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

	void ProgressBar::setValue(unsigned int value)
	{
		if (m_value != value && m_value - m_minimum <= m_maximum - m_minimum)
		{
			m_value = value;
		}
	}

	const unsigned int ProgressBar::getValue() const
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

	void ProgressBar::setValueTextVerticalAlighnment(VerticalTextAlignment valueTextVerticalAlignment)
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
		if (m_percentText.m_textString != percentTextString)
		{
			m_percentText.m_text.setString(percentTextString + "%");
			m_percentText.m_textString = percentTextString;
		}	
	}

	const std::string ProgressBar::getPercentTextString() const
	{
		return m_percentText.m_textString;
	}

	void ProgressBar::setPercentTextCharacterSize(unsigned int percentTextCharacterSize)
	{
		setCharacterSize(m_percentText, percentTextCharacterSize);
	}

	const unsigned int ProgressBar::getPercentTextCharacterSize() const
	{
		return getCharacterSize(m_percentText);
	}

	void ProgressBar::setPercentTextVerticalAlighnment(VerticalTextAlignment percentTextVerticalAlignment)
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

	void ProgressBar::setMainString(std::string string)
	{
		if (m_mainText.m_textString != string)
		{
			m_mainText.m_text.setString(string);
			m_mainText.m_textString = string;
		}
		
	}

	const std::string ProgressBar::getMainString() const
	{
		return std::string();
	}

	void ProgressBar::setMainTextCharacterSize(unsigned int mainTextCharacterSize)
	{
		setCharacterSize(m_mainText, mainTextCharacterSize);
	}

	const unsigned int ProgressBar::getMainTextCharacterSize() const
	{
		return getCharacterSize(m_mainText);
	}

	void ProgressBar::setMainTextVerticalAlighnment(VerticalTextAlignment mainTextVerticalAlignment)
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
		}
	}

	const ProgressBar::FillDirection ProgressBar::getFillDirection() const
	{
		return m_fillDirection;
	}

	void ProgressBar::onEvent(EventRoot& sender, KeyDownEvent& ev)
	{
		switch (ev.key)
		{
		case sf::Keyboard::Left:
			if (m_value > m_minimum)
			{
				--m_value;
			}
			break;
		case sf::Keyboard::Right:
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

	void ProgressBar::updateMainTextPosition()
	{
		auto textWidth = m_mainText.m_text.getLocalBounds().width;
		auto textHeight = m_mainText.m_text.getLocalBounds().height;
		auto xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
		auto yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
		m_mainText.m_text.setPosition(xPosition, yPosition);
	}

	void ProgressBar::updateMaximumTextPosition()
	{

	}

	void ProgressBar::updateMinimumTextPosition()
	{
	}

	void ProgressBar::updateValueTextPosition()
	{
	}

	void ProgressBar::updatePercentTextPosition()
	{
		auto textWidth = m_percentText.m_text.getLocalBounds().width;
		auto textHeight = m_percentText.m_text.getLocalBounds().height;
		auto xPosition = m_position.x + (m_size.x / 2 - textWidth / 2);
		auto yPosition = m_position.y + (m_size.y / 2 - textHeight / 2);
		m_percentText.m_text.setPosition(xPosition, yPosition);
	}

	void ProgressBar::updateMainTextString()
	{

	}

	void ProgressBar::updateMaximumTextString()
	{

	}

	void ProgressBar::updateMinimumTextString()
	{

	}

	void ProgressBar::updateValueTextString()
	{

	}

	void ProgressBar::updatePercentTextString()
	{
		int percent = calculatedPercent() * 100;
		setPercentTextString(std::to_string(percent));
	}

	void ProgressBar::updateFillDirection()
	{
		switch (m_fillDirection)
		{
		case FillDirection::LeftToRight:
			m_progressShape.setSize({ m_size.x * calculatedPercent(), m_size.y });
			break;
		case FillDirection::RightToLeft:
			m_progressShape.setSize({ m_size.x * (1 - calculatedPercent()), m_size.y });
			break;
		case FillDirection::TopToBottom:
			m_progressShape.setSize({ m_size.x, m_size.y * calculatedPercent() });
			break;
		case FillDirection::BottomToTop:
			m_progressShape.setSize({ m_size.x , m_size.y * (1 - calculatedPercent() )});
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

	void ProgressBar::setTextString(Text text, std::string string)
	{
		if (text.m_textString != string)
		{
			text.m_textString = string;
		}
	}

	void ProgressBar::setCharacterSize(Text text, unsigned int characterSize)
	{
		if (text.m_characterSize != characterSize)
		{
			text.m_characterSize = characterSize;
		}
	}

	const unsigned int ProgressBar::getCharacterSize(Text text) const
	{
		return text.m_characterSize;
	}

	void ProgressBar::setVerticalAlignment(Text text, VerticalTextAlignment verticalAlignment)
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

	void ProgressBar::setVisibility(Text text, bool isVisible)
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

	void ProgressBar::setFillColor(Text text, sf::Color color)
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
		m_text.setString(m_textString);
	}
}