#include "Label.h"

namespace ire::core::gui
{
	WidgetType const Label::m_type = WidgetType::create<Label>("Label");


	Label::Label()
	{
		setBackgroundShapeColor(sf::Color::Green);

		setCharacterSize(45);
		setTextVisible(true);
		setTextFillColor(sf::Color::White);

	}

	std::unique_ptr<Label> Label::create(const std::string& text)
	{
		auto widget = std::make_unique<Label>();
		widget->setTextString(text);
		return widget;
	}

	void Label::draw(sf::RenderTarget& target)
	{
		if (m_isBackgroundVisible)
		{
			target.draw(m_backgroundShape);
		}
		
		if (m_mainText.isVisible())
		{
			target.draw(m_mainText);
		}
	}

	void Label::updateWidget()
	{	
		m_mainText.setTextPosition(m_position, m_size);

		m_backgroundShape.setSize(m_size);
		m_backgroundShape.setPosition(m_position);

	}

	void Label::setTextString(const std::string& string)
	{
		if (m_mainText.getString() != string)
		{
			m_mainText.setString(string);
		}
	}

	const std::string Label::getTextString() const
	{
		return m_mainText.getString();
	}

	void Label::setCharacterSize(unsigned int characterSize)
	{
		if (m_mainText.getCharacterSize() != characterSize)
		{
			m_mainText.setCharacterSize(characterSize);
		}
	}

	const unsigned int Label::getCharacterSize() const
	{
		return m_mainText.getCharacterSize();
	}

	void Label::setVerticalAlignment(Text::VerticalAlignment verticalAlignment)
	{
		if (m_mainText.getVerticalAlign() != verticalAlignment)
		{
			m_mainText.setVerticalAlign(verticalAlignment);
		}
	}

	const Text::VerticalAlignment Label::getVerticalAlignment() const
	{
		return m_mainText.getVerticalAlign();
	}

	void Label::setHorizontalAlignment(Text::HorizontalAlignment horizontalAlignment)
	{
		if (m_mainText.getHorizontalAlign() != horizontalAlignment)
		{
			m_mainText.setHorizontalAlign(horizontalAlignment);
		}
	}

	const Text::HorizontalAlignment Label::getHorizontalAlignment() const
	{
		return m_mainText.getHorizontalAlign();
	}

	void Label::setTextVisible(bool isVisible)
	{
		if (m_mainText.isVisible() != isVisible)
		{
			m_mainText.setVisible(isVisible);
		}
	}

	const bool Label::isTextVisible() const
	{
		return m_mainText.isVisible();
	}

	void Label::setTextFillColor(sf::Color fillColor)
	{
		if (m_mainText.getFillColor() != fillColor)
		{
			m_mainText.setFillColor(fillColor);
		}
	}

	const sf::Color Label::getTextFillColor() const
	{
		return m_mainText.getFillColor();
	}

	void Label::setTextOutlineColor(sf::Color outlineColor)
	{
		if (m_mainText.getOutlineColor() != outlineColor)
		{
			m_mainText.setOutlineColor(outlineColor);
		}
	}

	const sf::Color Label::getTextOutlineColor() const
	{
		return m_mainText.getOutlineColor();
	}

	void Label::setTextOutlineThickness(float outlineThickness)
	{
		if (m_mainText.getOutlineThickness() != outlineThickness)
		{
			m_mainText.setOutlineThickness(outlineThickness);
		}
	}

	const float Label::getTextOutlineThickness() const
	{
		return m_mainText.getOutlineThickness();
	}

	void Label::setTextStyle(sf::Uint32 style)
	{
		if (m_mainText.getStyle() != style)
		{
			m_mainText.setStyle(style);
		}
	}

	void Label::setTextLatterSpacing(float spacingFactor)
	{
		if (m_mainText.getLetterSpacing() != spacingFactor)
		{
			m_mainText.setLetterSpacing(spacingFactor);
		}
	}

	void Label::setTextLineSpacing(float spacingFactor)
	{
		m_mainText.setLineSpacing(spacingFactor);
	}

	void Label::setTextFont(const std::string& pathToFont)
	{
		m_mainText.setFont(pathToFont);
	}
	void Label::setBackgroundShapeColor(sf::Color backgroundColor)
	{
		if (m_backgroundShape.getFillColor() != backgroundColor)
		{
			m_backgroundShape.setFillColor(backgroundColor);
		}
	}
	const sf::Color Label::getBackgroundShapeColor() const
	{
		return m_backgroundShape.getFillColor();
	}
	void Label::setBackgdoungVisibility(bool isBackgroundVisible)
	{
		if (m_isBackgroundVisible != isBackgroundVisible)
		{
			m_isBackgroundVisible = isBackgroundVisible;
		}
	}
	const bool Label::isBackgroundVisible() const
	{
		return m_isBackgroundVisible;
	}
}
