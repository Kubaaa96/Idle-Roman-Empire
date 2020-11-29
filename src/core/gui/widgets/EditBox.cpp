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

		//setGhostTextString("Ghost Text");

		m_ghostText.setFont(*m_font);
		m_ghostText.setCharacterSize(15);
		m_ghostText.setFillColor(sf::Color(140, 140, 140)); // Gray Color for Ghost text

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

		if (!m_text.getString().isEmpty())
		{
			target.draw(m_text);
		}
		else
		{
			target.draw(m_ghostText);
		}

	}

	void EditBox::updateWidget()
	{
		m_rectangleShape.setSize(m_size);
		m_rectangleShape.setPosition(m_position);

		m_text.setPosition(m_position.x + 15, m_position.y + 15);
		m_ghostText.setPosition(m_position.x + 15, m_position.y + 15);

		updateCaretPosition();
		m_caret.setSize(sf::Vector2f(2, 15));
	}

	void EditBox::setTextString(const std::string& string)
	{
		if (m_textString != string)
		{
			m_textString = string;
			m_text.setString(m_textString);
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
			m_ghostText.setString(m_ghostTextString);
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

		if (m_currentCaretPosition == charactersBeforeCaret)
		{
			m_currentCaretPosition = charactersBeforeCaret;
		}
	}

	const std::size_t EditBox::getCaretPosition() const
	{
		return m_currentCaretPosition;
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
		// Preventing Backspace from printing 
		if (ev.character == 8)
		{
			return;
		}
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
		// Unlimited Characters

		switch (m_maxChars)
		{
		case 0:
			m_textString.insert(m_currentCaretPosition, conv.to_bytes(ev.character));
			++m_currentCaretPosition;
			m_text.setString(m_textString);
			break;
		default:
			if (m_textString.length() < m_maxChars)
			{
				m_textString.insert(m_currentCaretPosition, conv.to_bytes(ev.character));
				++m_currentCaretPosition;
				m_text.setString(m_textString);
			}
			break;
		}
		updateCaretPosition();
		onTextChanged(ev);
	}

	void EditBox::onEvent(EventRoot& sender, KeyDownEvent& ev)
	{
		switch (ev.key)
		{
		case sf::Keyboard::Left:

			// CTRL + Left arrow Shortcut
			if (ev.control)
			{
				auto nextJumpIndex = m_textString.find_last_of(" \t", m_currentCaretPosition);
				if (m_currentCaretPosition == nextJumpIndex + 1)
				{
					nextJumpIndex = m_textString.find_last_of(" \t", m_currentCaretPosition - 2);
				}
				if (m_currentCaretPosition != 0 && nextJumpIndex < m_textString.length())
				{
					m_currentCaretPosition = nextJumpIndex + 1;
				}
				else
				{
					m_currentCaretPosition = 0;
				}
				break;
			}

			if (m_currentCaretPosition != 0)
			{
				--m_currentCaretPosition;
			}
			break;
		case sf::Keyboard::Right:
			// CTRL + Right Shortcut
			if (ev.control)
			{
				auto nextJumpIndex = m_textString.find_first_of(" \t", m_currentCaretPosition);
				if (m_currentCaretPosition == nextJumpIndex)
				{
					nextJumpIndex = m_textString.find_first_of(" \t", m_currentCaretPosition + 1);
				}
				if (nextJumpIndex < m_textString.length())
				{
					m_currentCaretPosition = nextJumpIndex + 1;
				}
				else
				{
					m_currentCaretPosition = m_textString.length();
				}
				break;
			}

			if (m_currentCaretPosition != m_textString.length())
			{
				++m_currentCaretPosition;
			}
			break;
		case sf::Keyboard::Backspace:
			if (m_currentCaretPosition != 0)
			{
				backspaceKeyPressed();

			}
			break;
		case sf::Keyboard::Delete:
			if (m_currentCaretPosition != m_textString.length())
			{
				deleteKeyPressed();
			}
			break;
		default:
			break;
		}
		updateCaretPosition();
		onKeyClicked(ev);
	}

	void EditBox::onEvent(EventRoot& sender, KeyUpEvent& ev)
	{

	}

	void EditBox::onTextChanged(TextEnteredEvent& ev)
	{
		TextChangedEvent textChangedEv{};
		textChangedEv.timestamp = ev.timestamp;
		textChangedEv.character = ev.character;
		emitEvent<TextChangedEvent>(textChangedEv);
	}
	void EditBox::onKeyReleased(KeyUpEvent& ev)
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
	void EditBox::onKeyClicked(KeyDownEvent& ev)
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

	void EditBox::backspaceKeyPressed()
	{
		m_textString.erase(m_currentCaretPosition - 1, 1);
		m_text.setString(m_textString);
		--m_currentCaretPosition;
		updateCaretPosition();
	}

	void EditBox::deleteKeyPressed()
	{
		m_textString.erase(m_currentCaretPosition, 1);
		m_text.setString(m_textString);
		updateCaretPosition();
	}

	void EditBox::updateCaretPosition()
	{
		auto positinOfFirstletter = m_text.findCharacterPos(m_currentCaretPosition);
		m_caret.setPosition(positinOfFirstletter.x - 1, positinOfFirstletter.y);
	}
}