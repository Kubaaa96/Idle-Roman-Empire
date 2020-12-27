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

	void Text::setHAlign(HorizontalAlignment horizontalAlignment)
	{
		if (m_horizontalAlignment != horizontalAlignment)
		{
			m_horizontalAlignment = horizontalAlignment;
		}
	}

	const Text::HorizontalAlignment Text::getHAlign() const
	{
		return m_horizontalAlignment;
	}

	void Text::setVAlign(VerticalAlignment verticalAlignment)
	{
		if (m_varticalAlignment != verticalAlignment)
		{
			m_varticalAlignment = verticalAlignment;
		}
	}

	const Text::VerticalAlignment Text::getVAlign() const
	{
		return m_varticalAlignment;
	}

	void Text::setVisibility(bool isVisible)
	{
		if (m_isVisible != isVisible)
		{
			m_isVisible = isVisible;
		}
	}

	const bool Text::getVisibility() const
	{
		return m_isVisible;
	}

	void Text::setFont(const std::string& pathToFont)
	{
		sf::Text::setFont(*ResourceManager::instance().get<sf::Font>(pathToFont));
	}

	void Text::updateTextPosition(float xPosition, float yPosition, sf::Vector2f currentPosition, sf::Vector2f currentSize)
	{
		auto textWidth{ getLocalBounds().width };
		auto textHeight{ getLocalBounds().height };
		auto letterSpacing{ getLetterSpacing() };
		
		if (m_isVAlign)
		{
			switch (m_varticalAlignment)
			{
			case VerticalAlignment::Bottom:
				yPosition = currentPosition.y + currentSize.y - textHeight - letterSpacing;
				break;
			case VerticalAlignment::Center:
				yPosition = currentPosition.y + (currentSize.y / 2 - textHeight / 2);
				break;
			case VerticalAlignment::Top:
				yPosition = currentPosition.y + letterSpacing;
				break;
			default:
				break;
			}
		}
		
		if (m_isHAlign)
		{
			switch (m_horizontalAlignment)
			{
			case ire::core::gui::Text::HorizontalAlignment::Left:
				xPosition = currentPosition.x + letterSpacing;
				break;
			case ire::core::gui::Text::HorizontalAlignment::Right:
				xPosition = currentPosition.x + currentSize.x - textHeight - letterSpacing;
				break;
			case ire::core::gui::Text::HorizontalAlignment::Center:
				xPosition = currentPosition.x + (currentSize.x / 2 - textHeight / 2);
				break;
			default:
				break;
			}
		}
		setPosition(xPosition, yPosition);
	}
}