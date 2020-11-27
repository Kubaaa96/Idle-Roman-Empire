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
		//m_text.setLetterSpacing(0.75);


		m_caret.setFillColor(sf::Color::Red);

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
		target.draw(m_caret);

		target.draw(m_text);
	}

	void EditBox::updateWidget()
	{
		m_rectangleShape.setSize(m_size);
		m_rectangleShape.setPosition(m_position);

		m_text.setPosition(m_position.x + 15, m_position.y + 15);

		auto positinOfFirstletter = m_text.findCharacterPos(m_currentCaretPosition);
		m_caret.setPosition(positinOfFirstletter.x - 1, positinOfFirstletter.y);
		m_caret.setSize(sf::Vector2f(1, 15));
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
		if (charactersBeforeCaret > m_textString.length())
		{
			charactersBeforeCaret = m_textString.length();
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
		m_textString.append(conv.to_bytes(ev.character));
		m_text.setString(m_textString);
		//std::cout << m_textString << "\n";
		onTextChanged(ev);
	}

	void EditBox::onEvent(EventRoot& sender, KeyDownEvent& ev)
	{
	}

	void EditBox::onEvent(EventRoot& sender, KeyUpEvent& ev)
	{
		switch (ev.key)
		{
		case sf::Keyboard::Left:
			if (ev.control)
			{
				std::cout << "Left + CTRL Released\n";
				break;
			}
			if (m_currentCaretPosition != 0)
			{
				--m_currentCaretPosition;
			}
			break;
		case sf::Keyboard::Right:
			if (ev.control)
			{
				std::cout << "Right + CTRL Released\n";
				break;
			}
			
			if (m_currentCaretPosition != m_textString.length())
			{
				++m_currentCaretPosition;
			}
			break;
		default:
			break;
		}
		updateWidget();
		onKeyClicked(ev);
	}

	void EditBox::onTextChanged(TextEnteredEvent& ev)
	{
		TextChangedEvent textChangedEv{};
		textChangedEv.timestamp = ev.timestamp;
		textChangedEv.characters = ev.character;
		emitEvent<TextChangedEvent>(textChangedEv);
	}
	void EditBox::onKeyClicked(KeyUpEvent& ev)
	{
		KeyReleasedEvent keyClickedEv{};
		keyClickedEv.timestamp = ev.timestamp;
		keyClickedEv.key = ev.key;
		keyClickedEv.alt = ev.alt;
		keyClickedEv.control = ev.control;
		keyClickedEv.shift = ev.control;
		keyClickedEv.system = ev.system;
		emitEvent<KeyReleasedEvent>(keyClickedEv);
	}
}