#include "Text.h"

namespace ire::core::gui
{
	Text::Text(std::string string, sf::Color fillColor,
		sf::Color outlineColor, unsigned int characterSize)
	{
		setFont("resource/RomanSD.ttf");
		setString(string);
		setFillColor(fillColor);
		setOutlineColor(outlineColor);
		setOutlineThickness(2);
		setCharacterSize(characterSize);
	}

	void Text::setHorizontalAlign(HorizontalAlignment horizontalAlignment)
	{
		if (m_horizontalAlignment != horizontalAlignment)
		{
			m_horizontalAlignment = horizontalAlignment;
		}
	}

	const Text::HorizontalAlignment Text::getHorizontalAlign() const
	{
		return m_horizontalAlignment;
	}

	void Text::setVerticalAlign(VerticalAlignment verticalAlignment)
	{
		if (m_varticalAlignment != verticalAlignment)
		{
			m_varticalAlignment = verticalAlignment;
		}
	}

	const Text::VerticalAlignment Text::getVerticalAlign() const
	{
		return m_varticalAlignment;
	}

	void Text::setVisible(bool isVisible)
	{
		if (m_isVisible != isVisible)
		{
			m_isVisible = isVisible;
		}
	}

	const bool Text::isVisible() const
	{
		return m_isVisible;
	}

	void Text::setFont(const std::string& pathToFont)
	{
		sf::Text::setFont(*ResourceManager::instance().get<sf::Font>(pathToFont));
	}

	void Text::setTextPosition(sf::Vector2f positionOfWidget, sf::Vector2f sizeOfWidget)
	{
		auto textWidth{ getLocalBounds().width };
		auto textHeight{ getLocalBounds().height };
		auto letterSpacing{ getLetterSpacing() };

		float xPosition = 0;
		float yPosition = 0;
		switch (m_varticalAlignment)
		{
		case VerticalAlignment::Bottom:
			yPosition = positionOfWidget.y + sizeOfWidget.y - textHeight - letterSpacing;
			break;
		case VerticalAlignment::Center:
			yPosition = positionOfWidget.y + (sizeOfWidget.y / 2 - textHeight / 2);
			break;
		case VerticalAlignment::Top:
			yPosition = positionOfWidget.y + letterSpacing;
			break;
		default:
			break;
		}
		
		switch (m_horizontalAlignment)
		{
		case ire::core::gui::Text::HorizontalAlignment::Left:
			xPosition = positionOfWidget.x + letterSpacing;
			break;
		case ire::core::gui::Text::HorizontalAlignment::Right:
			xPosition = positionOfWidget.x + sizeOfWidget.x - textWidth - letterSpacing;
			break;
		case ire::core::gui::Text::HorizontalAlignment::Center:
			xPosition = positionOfWidget.x + (sizeOfWidget.x / 2 - textWidth / 2);
			break;
		default:
			break;
		}
		
		setPosition(xPosition, yPosition);
	}
}