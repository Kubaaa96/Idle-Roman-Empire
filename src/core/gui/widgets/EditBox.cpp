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

		m_ghostText.setFont(*m_font);
		m_ghostText.setCharacterSize(15);
		m_ghostText.setFillColor(sf::Color(140, 140, 140)); // Gray Color for Ghost text

		m_caret.setFillColor(sf::Color::Red);
		m_caret.setSize(sf::Vector2f(2, static_cast<float>(m_characterSize)));

		m_selection.setFillColor(sf::Color(0, 191, 255, 127));

		m_rectangleShape.setFillColor(sf::Color::White);
		m_rectangleShape.setOutlineColor(sf::Color::Blue);
		m_rectangleShape.setOutlineThickness(3);

		initializeSelection();
	}

	std::unique_ptr<EditBox> EditBox::create(const std::string& text)
	{
		auto widget = std::make_unique<EditBox>();
		widget->setTextString(text);
		return widget;
	}

	void EditBox::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);

		if (m_state != State::Idle)
		{
			target.draw(m_caret);
		}
		
		if (m_selStarting != m_selIndex && m_isSelectingActive)
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
			switch (m_maxChars)
			{
			case 0:
				m_textString = string;
				m_text.setString(m_textString);
				break;
			default:			
				if (string.length() > m_maxChars)
				{
					m_textString = string;
					m_text.setString(m_textString);
				}
				else
				{
					throw std::runtime_error("Choosen string is not fitting because of Max character limit Try setMaximumCharacters");
				}
				break;
			}

			// TODO Cut String if it is longer than m_maxChar and give info to client

		}
	}

	const std::string& EditBox::getTextString() const
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
			m_textString.erase(m_maxChars);
			m_text.setString(m_textString);
		}
	}

	const unsigned int EditBox::getMaximumCharacters() const
	{
		return m_maxChars;
	}

	void EditBox::onEvent(EventRoot& sender, TextEnteredEvent& ev)
	{
		// Preventing Backspace, CTRL + C, CTRL + X, CTRL + V, CTRL + A from printing 
		if (ev.character == 8 || ev.character == 3 || ev.character == 24 
			|| ev.character == 22 || ev.character == 1)
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
		m_isSelectingActive = false;
		updateIndexesOfWordStarting();
		updateCaretPosition();
		onTextChanged(ev);
	}

	void EditBox::onEvent(EventRoot& sender, KeyDownEvent& ev)
	{
		switch (ev.key)
		{
		case sf::Keyboard::Left:

			if (ev.control)
			{
				if (!indexesOfWordStarting.empty() && m_currentCaretPosition != 0)
				{		
					auto valueSmaller = std::lower_bound(indexesOfWordStarting.rbegin(),
						indexesOfWordStarting.rend(), m_currentCaretPosition - 1, std::greater<std::size_t>());

					// CTRL + SHIFT + LEFT
					if (ev.shift)
					{
						if (!m_isSelectingActive)
						{
							initializeSelection();
						}
						m_selIndex = *valueSmaller;
						m_isSelectingActive = true;
						updateSelectionPosition();
					}
					// CTRL + Left 
					m_currentCaretPosition = *valueSmaller;
					break;
				}
			}
			// SHIFT + LEFT
			if (ev.shift)
			{
				// Prevent from going from 0 to std::size_t max value
				if (!m_isSelectingActive)
				{
					initializeSelection();
				}

				if (m_selIndex > 0)
				{
					--m_selIndex;
					m_currentCaretPosition = m_selIndex;
				}
				
				if (m_selIndex == m_selStarting)
				{
					m_isSelectingActive = false;
					break;
				}
				else
				{
					m_isSelectingActive = true;
				}
				
				updateSelectionPosition();
				break;
			}
			if (m_isSelectingActive && m_selIndex > 0)
			{
				if (m_selIndex == m_selStarting)
				{
					--m_currentCaretPosition;
				}
				else if (m_selIndex > m_selStarting)
				{
					m_currentCaretPosition = m_selStarting;
				}
				initializeSelection();
				m_isSelectingActive = false;
				break;
			}
			if (m_currentCaretPosition > 0 )
			{
				--m_currentCaretPosition;
			}
			break;
		case sf::Keyboard::Right:

			if (ev.control)
			{
				if (!indexesOfWordStarting.empty() && m_currentCaretPosition != m_textString.length())
				{				
					auto valueGreater = std::upper_bound(indexesOfWordStarting.begin(),
						indexesOfWordStarting.end(), m_currentCaretPosition);
					// CTRL + SHIFT + RIGHT
					if (ev.shift)
					{
						if (!m_isSelectingActive)
						{
							initializeSelection();
						}
						m_selIndex = *valueGreater;
						m_isSelectingActive = true;
						updateSelectionPosition();
					}
					// CTRL + Right
					m_currentCaretPosition = *valueGreater;
					break;
				}
			}

			// SHIFT + RIGHT
			if (ev.shift)
			{
				if (!m_isSelectingActive)
				{
					initializeSelection();
				}
				if (m_selIndex < m_textString.length())
				{
					++m_selIndex;
					m_currentCaretPosition = m_selIndex;
				}
				
				if (m_selIndex == m_selStarting)
				{
					m_isSelectingActive = false;
					break;
				}
				else
				{
					m_isSelectingActive = true;
				}
				updateSelectionPosition();
				break;
			}

			if (m_isSelectingActive && m_selIndex < m_textString.length())
			{
				if (m_selIndex == m_selStarting)
				{
					++m_currentCaretPosition;
				}
				else if (m_selIndex < m_selStarting)
				{
					m_currentCaretPosition = m_selStarting;
				}
				initializeSelection();
				m_isSelectingActive = false;
				break;
			}

			if (m_currentCaretPosition < m_textString.length())
			{
				++m_currentCaretPosition;
			}
			break;

		case sf::Keyboard::C:
			if (ev.control)
			{
				if (!m_selectedString.empty())
				{
					sf::Clipboard::setString(m_selectedString);
				}
			}
			break;

		case sf::Keyboard::X:
			if (ev.control)
			{
				if (!m_selectedString.empty())
				{
					sf::Clipboard::setString(m_selectedString);
					eraseSelectedFromString();
					m_isSelecting = false;
					m_text.setString(m_textString);
				}	
				updateIndexesOfWordStarting();
				initializeSelection();
				updateSelectionPosition();
			}
			break;

		case sf::Keyboard::V:
			if (ev.control)
			{
				auto stringFromClipboard = sf::Clipboard::getString().toAnsiString();
				if (!stringFromClipboard.empty())
				{
					if (!m_selectedString.empty())
					{
						eraseSelectedFromString();
					}
					m_textString.insert(m_currentCaretPosition, stringFromClipboard);
					m_currentCaretPosition = m_currentCaretPosition + stringFromClipboard.length();
				}
				m_text.setString(m_textString);
				updateIndexesOfWordStarting();
				initializeSelection();
				updateSelectionPosition();
			}
			break;

		case sf::Keyboard::A:
			if (ev.control)
			{
				if (!m_textString.empty())
				{
					m_selStarting = 0;
					m_selIndex = m_textString.length();
					m_isSelectingActive = true;
					m_currentCaretPosition = m_selIndex;
				}
				updateSelectionPosition();
				updateCaretPosition();
			}
			break;

		case sf::Keyboard::Backspace:
			deleteOneLetterBeforeCaret();		
			break;
		case sf::Keyboard::Delete:
			deleteOneLetterAfterCaret();
			break;
		default:
			break;
		}
		ev.handled = true;
		updateCaretPosition();
		onKeyClicked(ev);
	}

	void EditBox::onEvent(EventRoot& sender, MouseButtonDownEvent& ev)
	{
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
			m_isSelecting = true;
			m_isSelectingActive = true;

			updateSelectionPosition();
			updateCaretPosition();
			break;
		case sf::Mouse::Button::Right:
			std::cout << "Context Menu\n";
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

		if (m_selIndex != m_selStarting)
		{
			m_isSelectingActive = true;
		}
		else
		{
			m_isSelectingActive = false;
		}

		m_isSelecting = false;
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

			if (m_isSelecting)
			{
				auto clickedXPosition = ev.position.x;
				auto positionOfRight = m_text.getGlobalBounds().left + m_text.getGlobalBounds().width;
				if (clickedXPosition < positionOfRight)
				{
					auto currentIndexOfLetter = findIndexOfLetterUnderMouse(clickedXPosition);
					m_currentCaretPosition = currentIndexOfLetter;
					m_selIndex = currentIndexOfLetter;
				}
				else
				{
					m_currentCaretPosition = m_textString.length();
					m_selIndex = m_textString.length();

				}
				positionsOfLetters.clear();
				distanceToLetters.clear();
				updateSelectionPosition();
				updateCaretPosition();
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
			sender.resetActiveWidget(*this);
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

	void EditBox::deleteOneLetterBeforeCaret()
	{
		if (m_currentCaretPosition < m_textString.length() + 1)
		{
			m_textString.erase(m_currentCaretPosition - 1, 1);
			m_text.setString(m_textString);
			--m_currentCaretPosition;
			updateIndexesOfWordStarting();
			initializeSelection();
			updateCaretPosition();
		}
	}

	void EditBox::deleteOneLetterAfterCaret()
	{
		if (m_currentCaretPosition >= 0)
		{
			m_textString.erase(m_currentCaretPosition, 1);
			m_text.setString(m_textString);
			updateIndexesOfWordStarting();
			initializeSelection();
			updateCaretPosition();
		}
	}

	void EditBox::eraseSelectedFromString()
	{
		if (m_selStarting < m_selIndex)
		{
			m_textString.erase(m_selStarting, m_selIndex - m_selStarting);
			m_currentCaretPosition = m_selStarting;
		}
		else
		{
			m_textString.erase(m_selIndex, m_selStarting - m_selIndex);
			m_currentCaretPosition = m_selIndex;
		}
	}

	void EditBox::updateCaretPosition()
	{
		auto positinOfFirstletter = m_text.findCharacterPos(m_currentCaretPosition);
		m_caret.setPosition(positinOfFirstletter.x - 1, positinOfFirstletter.y);
	}

	void EditBox::updateIndexesOfWordStarting()
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
		indexesOfWordStarting = tempIndexes;
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
		m_selStarting = m_currentCaretPosition;
		m_selIndex = m_currentCaretPosition;
	}

	void EditBox::updateSelectionPosition()
	{
		if (m_selStarting == m_selIndex)
		{
			return;
		}
		float widthOfSelection = 0;
		if (m_selStarting < m_selIndex)
		{
			m_selection.setPosition(m_text.findCharacterPos(m_selStarting));
			widthOfSelection = m_text.findCharacterPos(m_selIndex).x -
				m_text.findCharacterPos(m_selStarting).x;
			m_selectedString = m_textString.substr(m_selStarting, m_selIndex - m_selStarting);
		}
		else 
		{
			m_selection.setPosition(m_text.findCharacterPos(m_selIndex));
			widthOfSelection = m_text.findCharacterPos(m_selStarting).x -
				m_text.findCharacterPos(m_selIndex).x;
			m_selectedString = m_textString.substr(m_selIndex, m_selStarting - m_selIndex);
			
		}
		m_selection.setSize({ widthOfSelection, static_cast<float>(m_characterSize + 2) });
	}

}