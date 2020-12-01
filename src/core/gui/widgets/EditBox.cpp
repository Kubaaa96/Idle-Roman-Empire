#include "EditBox.h"
#include <codecvt>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace ire::core::gui
{
	WidgetType const EditBox::m_type = WidgetType::create<EditBox>("EditBox");

	EditBox::EditBox()
	{
		m_font = ResourceManager::instance().get<sf::Font>("resource/RomanSD.ttf");
		m_text.setFont(*m_font);
		m_text.setCharacterSize(m_characterSize);
		m_text.setFillColor(sf::Color::Black);

		//setGhostTextString("Ghost Text");

		m_ghostText.setFont(*m_font);
		m_ghostText.setCharacterSize(15);
		m_ghostText.setFillColor(sf::Color(140, 140, 140)); // Gray Color for Ghost text

		m_caret.setFillColor(sf::Color::Red);
		m_caret.setSize(sf::Vector2f(2, m_characterSize));

		m_selection.setFillColor(sf::Color(0, 191, 255, 127));

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

		if (m_state != State::Idle)
		{
			target.draw(m_caret);
		}
		
		if (m_selStart != m_selEnd)
		{
			target.draw(m_selection);
		}

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

		updateSelectionPosition();
		updateCaretPosition();

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

	void EditBox::setCharacterSize(unsigned int characterSize)
	{
		if (m_characterSize != characterSize)
		{
			m_characterSize = characterSize;
		}
	}

	const unsigned int EditBox::getCharacterSize() const
	{
		return m_characterSize;
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

		switch (m_maxChars)
		{
		// Unlimited Characters
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
		ev.handled = true;
		indexesOfWordStarting = setIndexesWhereWordsStarts();
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
				if (!indexesOfWordStarting.empty() && m_currentCaretPosition != 0)
				{
					auto firstOccurance = std::lower_bound(indexesOfWordStarting.rbegin(),
						indexesOfWordStarting.rend(), m_currentCaretPosition - 1, std::greater<std::size_t>());
					m_currentCaretPosition = *firstOccurance;
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
				if (!indexesOfWordStarting.empty() && m_currentCaretPosition != m_textString.length())
				{
					auto valueGreater = std::upper_bound(indexesOfWordStarting.begin(),
						indexesOfWordStarting.end(), m_currentCaretPosition);
					m_currentCaretPosition = *valueGreater;
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
		ev.handled = true;
		updateCaretPosition();
		onKeyClicked(ev);
	}

	void EditBox::onEvent(EventRoot& sender, KeyUpEvent& ev)
	{
		ev.handled = true;
	}

	void EditBox::onEvent(EventRoot& sender, MouseButtonDownEvent& ev)
	{
		// Setting Caret in clicked position.x
		auto clickedXPosition = ev.position.x;
		auto positionOfRight = m_text.getGlobalBounds().left + m_text.getGlobalBounds().width;
		switch (ev.button)
		{
		case sf::Mouse::Button::Left:		
			if (clickedXPosition < positionOfRight)
			{

				m_currentCaretPosition = findIndexOfLetterUnderMouse(clickedXPosition);
				positionsOfLetters.clear();
				distanceToLetters.clear();
			}
			else
			{
				m_currentCaretPosition = m_textString.length();
			}

			initializeSelection();
			m_isSelectingWithMouse = true;

			updateSelectionPosition();
			updateCaretPosition();
			break;
		case sf::Mouse::Button::Right:
			break;
		case sf::Mouse::Button::Middle:
			break;
		default:
			break;
		}
		m_state = State::Armed;
		ev.handled = true;
	}

	void EditBox::onEvent(EventRoot& sender, MouseButtonUpEvent& ev)
	{
		if (ev.button != sf::Mouse::Button::Left)
		{
			return;
		}

		if (m_state == State::Armed && clientBounds().contains(ev.position))
		{
			onClick(ev);
		}
		m_isSelectingWithMouse = false;
		m_state = State::Idle;
		ev.handled = true;

		sender.resetActiveWidget(*this);
	}

	void EditBox::onEvent(EventRoot& sender, MouseMovedEvent& ev)
	{
		if (clientBounds().contains(ev.position))
		{
			m_state = (
				(m_state == State::Idle || m_state == State::Hover)
				? State::Hover
				: State::Armed);

			if (m_isSelectingWithMouse)
			{
				auto clickedXPosition = ev.position.x;
				auto positionOfRight = m_text.getGlobalBounds().left + m_text.getGlobalBounds().width;
				if (clickedXPosition < positionOfRight)
				{
					auto currentIndexOfLetter = findIndexOfLetterUnderMouse(clickedXPosition);

					if (currentIndexOfLetter > m_previousPositionOfMouse)
					{
						m_selEnd = currentIndexOfLetter;
					}
					else
					{
						m_selStart = currentIndexOfLetter;
					}				
				}
				else
				{
					m_selStart = m_currentCaretPosition;
					m_selEnd = m_textString.length();
				}
				positionsOfLetters.clear();
				distanceToLetters.clear();
				updateSelectionPosition();
			}
		}
		else
		{
			m_state =
				(m_state == State::Armed || m_state == State::Disarmed)
				? State::Disarmed
				: State::Idle;
		}

		ev.handled = true;

		if (m_state == State::Idle)
		{
			//sender.resetActiveWidget(*this);
		}
		else
		{
			sender.setActiveWidget(*this);
		}
	}

	void EditBox::onTextChanged(TextEnteredEvent& ev)
	{
		TextChangedEvent textChangedEv{};
		textChangedEv.timestamp = ev.timestamp;
		textChangedEv.character = ev.character;
		emitEvent<TextChangedEvent>(textChangedEv);
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
		indexesOfWordStarting = setIndexesWhereWordsStarts();
		initializeSelection();
		updateCaretPosition();
	}

	void EditBox::deleteKeyPressed()
	{
		m_textString.erase(m_currentCaretPosition, 1);
		m_text.setString(m_textString);
		indexesOfWordStarting = setIndexesWhereWordsStarts();
		initializeSelection();
		updateCaretPosition();
	}

	void EditBox::updateCaretPosition()
	{
		auto positinOfFirstletter = m_text.findCharacterPos(m_currentCaretPosition);
		m_caret.setPosition(positinOfFirstletter.x - 1, positinOfFirstletter.y);
	}
	std::vector<std::size_t> EditBox::setIndexesWhereWordsStarts()
	{
		std::vector<std::size_t> tempIndexes{};
		if (!m_textString.empty())
		{
			tempIndexes.push_back(0); // Start of the Text
			tempIndexes.push_back(m_textString.length()); // End of the text
			for (std::size_t i = 1; i < m_textString.length(); ++i)
			{
				if (m_textString.at(i) != ' ' && m_textString.at(i) != '\t')
				{
					if (m_textString.at(i - 1) == ' ' || m_textString.at(i - 1) == '\t')
					{
						tempIndexes.push_back(i);
					}
				}
			}
		}
		std::sort(tempIndexes.begin(), tempIndexes.end());
		return tempIndexes;
	}

	std::size_t EditBox::findIndexOfLetterUnderMouse(float clickedXPosition)
	{
		for (std::size_t i = 0; i < m_textString.length(); ++i)
		{
			positionsOfLetters.push_back(m_text.findCharacterPos(i).x);
		}
		if (positionsOfLetters.empty())
		{
			return m_currentCaretPosition;
		}
		for (auto position : positionsOfLetters)
		{
			distanceToLetters.push_back(std::abs(position - clickedXPosition));
		}
		return std::min_element(distanceToLetters.begin(),
			distanceToLetters.end()) - distanceToLetters.begin();
	}

	void EditBox::initializeSelection()
	{
		m_selStart = m_currentCaretPosition;
		m_selEnd = m_currentCaretPosition;
		m_previousPositionOfMouse = m_currentCaretPosition;
	}

	void EditBox::updateSelectionPosition()
	{
		m_selection.setPosition(m_text.findCharacterPos(m_selStart));
		auto widthOfSelection = m_text.findCharacterPos(m_selEnd).x -
			m_text.findCharacterPos(m_selStart).x;
		m_selection.setSize({ widthOfSelection, static_cast<float>(m_characterSize + 2) });

		m_selectedString = m_textString.substr(m_selStart, m_selEnd - m_selStart);
	}

}