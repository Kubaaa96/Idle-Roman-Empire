#include "EditBox.h"
#include <codecvt>
#include <iostream>

namespace ire::core::gui
{
	WidgetType const EditBox::m_type = WidgetType::create<EditBox>("EditBox");

	EditBox::EditBox()
	{
		m_font = ResourceManager::instance().get<sf::Font>("resource/RomanSD.ttf");
		m_text.setFont(*m_font);
		m_text.setCharacterSize(15);
		m_text.setFillColor(sf::Color::Black);
		m_text.setStyle(sf::Text::Bold);


		m_caret.setFillColor(sf::Color::Black);

		m_rectangleShape.setFillColor(sf::Color::White);
		m_rectangleShape.setOutlineColor(sf::Color::Blue);
		m_rectangleShape.setOutlineThickness(3);
	}

	std::unique_ptr<EditBox> EditBox::create(const std::string& text)
	{
		auto widget = std::make_unique<EditBox>();
		// Setting up text on Button in future
		return widget;
	}

	void EditBox::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);

		if (++m_caretCounter >= m_caretBlinkingFrequency)
		{
			//target.draw(m_caret);
			m_caretCounter = 0;
		}
		target.draw(m_text);
	}

	void EditBox::updateWidget()
	{
		m_rectangleShape.setSize(m_size);
		m_rectangleShape.setPosition(m_position);


		m_text.setPosition(m_position.x + 15, m_position.y + 15);

		m_caret.setPosition(m_position.x + 15, m_position.y + 15);
		m_caret.setSize(sf::Vector2f(2, 15));
	}

	void EditBox::setTextString(const std::string& string)
	{
		if (m_textString != string)
		{
			m_textString = string;
		}
	}

	const std::string EditBox::getTextString() const
	{
		return m_textString;
	}

	void EditBox::setGhostTextString(const std::string& ghostString)
	{
		if (m_ghostTextString != ghostString)
		{
			m_ghostTextString = ghostString;
		}
	}

	const std::string EditBox::getGhostTextString() const
	{
		return m_ghostTextString;
	}

	void EditBox::setCaretPosition(std::size_t charactersBeforeCaret)
	{
		if (charactersBeforeCaret > m_textString.getSize())
		{
			charactersBeforeCaret = m_textString.getSize();
		}
	}

	const std::size_t EditBox::getCaretPosition() const
	{
		return std::size_t();
	}

	void EditBox::setReadOnly(bool readOnly)
	{
		if (m_readOnly != readOnly)
		{
			m_readOnly = readOnly;
		}
	}

	bool EditBox::isReadOnly() const
	{
		return m_readOnly;
	}

	void EditBox::setTextSize(unsigned int textSize)
	{
	}

	const unsigned int EditBox::getTextSize() const
	{
		return 0;
	}

	void EditBox::setAlignment(Alignment alignment)
	{
		if (m_textAlignment != alignment)
		{
			m_textAlignment = alignment;
		}
	}

	const Alignment EditBox::getAlignment() const
	{
		return m_textAlignment;
	}

	void EditBox::setMaximumCharacters(unsigned int maxChars)
	{
		if (m_maxChars != maxChars)
		{
			m_maxChars = maxChars;
			// TODO Erasing all characters that are after maxChar position
		}
	}

	const unsigned int EditBox::getMaximumCharacters() const
	{
		return m_maxChars;
	}

	void EditBox::onEvent(EventRoot& sender, TextEnteredEvent& ev)
	{
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
		m_stringText.append(conv.to_bytes(ev.character));
		m_text.setString(m_stringText);
		std::cout << m_stringText << "\n";
		onTextChanged(ev);
	}

	void EditBox::onTextChanged(TextEnteredEvent& ev)
	{
		TextChangedEvent textChangedEv{};
		textChangedEv.timestamp = ev.timestamp;
		textChangedEv.characters = ev.character;
		emitEvent<TextChangedEvent>(textChangedEv);
	}
}