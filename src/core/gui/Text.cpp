#include "Text.h"

namespace ire::core::gui
{
	Text::Text(sf::String& string, sf::Color fillColor = sf::Color::Black,
		sf::Color outlineColor = sf::Color::White, unsigned int characterSize = 15)
	{
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
}