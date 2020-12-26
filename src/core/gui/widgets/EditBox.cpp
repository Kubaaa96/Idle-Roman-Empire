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
        updateWordIndices();
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
        m_text.setCharacterSize(m_characterSize);
        m_ghostText.setPosition(m_position.x + 15, m_position.y + 15);
        m_ghostText.setCharacterSize(m_characterSize);

        m_caret.setSize(sf::Vector2f(2, static_cast<float>(m_characterSize)));

        updateSelectionPosition();
        updateCaretPosition();
    }

    void EditBox::setTextString(const std::string& string)
    {
        if (m_textString != string)
        {
            if (!m_maxChars || string.length() < *m_maxChars)
            {
                m_textString = string;
                m_text.setString(m_textString);
            }
            else
            {
                m_textString = string.substr(0, *m_maxChars);
                m_text.setString(m_textString);
            }        
        }
        updateWordIndices();
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
            updateWidget();
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

        if (m_currentCaretPosition != charactersBeforeCaret)
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
        if (*m_maxChars != maxChars)
        {
            m_maxChars = maxChars;
            if (m_textString.length() > *m_maxChars)
            {
                m_textString.erase(*m_maxChars);
                m_text.setString(m_textString);              
            }
        }
    }

    const unsigned int EditBox::getMaximumCharacters() const
    {
        return *m_maxChars;
    }

    void EditBox::onEvent(EventRoot& sender, TextEnteredEvent& ev)
    {
        if (ev.character < 32 || ev.character > 128)
        {
            return;
        }
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;

        if (m_isSelectingActive)
        {
            deleteSelected();
        }

        if (!m_maxChars || m_textString.length() < *m_maxChars)
        {
            m_textString.insert(m_currentCaretPosition, conv.to_bytes(ev.character));
            ++m_currentCaretPosition;
            m_text.setString(m_textString);
        }

        ev.handled = true;
        m_isSelectingActive = false;
        updateWordIndices();
        updateCaretPosition();
        //onTextChanged(ev);
        emitEvent(ev);
    }
    
    void EditBox::onEvent(EventRoot& sender, KeyDownEvent& ev)
    {
        switch (ev.key)
        {
        case sf::Keyboard::Left:

            if (ev.control)
            {
                if (!m_indexesOfWordStarting.empty() && m_currentCaretPosition != 0)
                {
                    auto valueSmaller = std::lower_bound(m_indexesOfWordStarting.rbegin(),
                        m_indexesOfWordStarting.rend(), m_currentCaretPosition - 1, std::greater<std::size_t>());

                    // CTRL + SHIFT + LEFT
                    if (ev.shift)
                    {
                        selectToWordStartIndex(*valueSmaller);
                    }
                    // CTRL + Left 
                    m_currentCaretPosition = *valueSmaller;
                    break;
                }
            }
            // SHIFT + LEFT
            if (ev.shift)
            {
                moveAndSelectByOne(ev.key);

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
            // Moving to Left index of selection with Left arrow
            if (m_isSelectingActive && m_selIndex >= 0)
            {
                if (m_selIndex > m_selStarting)
                {
                    m_currentCaretPosition = m_selStarting;
                }

                initializeSelection();
                m_isSelectingActive = false;
                break;
            }
            if (m_currentCaretPosition > 0)
            {
                --m_currentCaretPosition;
            }
            break;

        case sf::Keyboard::Right:

            if (ev.control)
            {
                if (!m_indexesOfWordStarting.empty() && m_currentCaretPosition != m_textString.length())
                {
                    auto valueGreater = std::upper_bound(m_indexesOfWordStarting.begin(),
                        m_indexesOfWordStarting.end(), m_currentCaretPosition);
                    // CTRL + SHIFT + RIGHT
                    if (ev.shift)
                    {
                        selectToWordStartIndex(*valueGreater);
                    }
                    // CTRL + Right
                    m_currentCaretPosition = *valueGreater;
                    break;
                }
            }

            // SHIFT + RIGHT
            if (ev.shift)
            {
                moveAndSelectByOne(ev.key);

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

            // Moving to right index of selection with Right arrow
            if (m_isSelectingActive && m_selIndex <= m_textString.length())
            {
                if (m_selIndex < m_selStarting)
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
                updateWordIndices();
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
                    if (m_maxChars && m_textString.length() > *m_maxChars)
                    {
                        m_textString.erase(*m_maxChars);
                    }
                    if (m_currentCaretPosition + stringFromClipboard.length() > * m_maxChars)
                    {
                        m_currentCaretPosition = m_textString.length();
                    }
                    else
                    {
                        m_currentCaretPosition = m_currentCaretPosition + stringFromClipboard.length();

                    }
                }
                m_text.setString(m_textString);
                updateWordIndices();
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
            if (m_currentCaretPosition >= 0)
            {          
                if (m_isSelectingActive)
                {
                    deleteSelected();
                }
                else
                {
                    deleteCharacterAt(m_currentCaretPosition - 1);
                    if (m_currentCaretPosition > 0)
                    {
                        --m_currentCaretPosition;
                    }                  
                }
                
                updateCaretPosition();
            }
            break;

        case sf::Keyboard::Delete:
            if (m_currentCaretPosition < m_textString.length() + 1)
            {
                if (m_isSelectingActive)
                {
                    deleteSelected();
                }
                else
                {
                    deleteCharacterAt(m_currentCaretPosition);
                }
                updateCaretPosition();
            }
            break;

        case sf::Keyboard::Home:
            if (ev.shift)
            {
                if (!m_isSelectingActive)
                {
                    initializeSelection();
                    m_isSelectingActive = true;
                }
                m_selStarting = 0;
                m_currentCaretPosition = m_selStarting;
                updateSelectionPosition();
                break;
            }
            if (m_isSelectingActive || m_currentCaretPosition != 0)
            {
                m_currentCaretPosition = 0;
                initializeSelection();
                m_isSelectingActive = false;
            }
            break;

        case sf::Keyboard::End:
            if (ev.shift)
            {
                if (!m_isSelectingActive)
                {
                    initializeSelection();
                    m_isSelectingActive = true;
                }
                m_selIndex = m_textString.length();
                m_currentCaretPosition = m_selIndex;
                updateSelectionPosition();
                break;
            }
            if (m_isSelectingActive || m_currentCaretPosition != m_textString.length())
            {
                m_currentCaretPosition = m_textString.length();
                initializeSelection();
                m_isSelectingActive = false;
            }

            break;
        default:
            break;
        }
        ev.handled = true;
        updateCaretPosition();
        //onKeyClicked(ev);
        emitEvent(ev);
    }

    void EditBox::moveAndSelectOneToLeft()
    {
        if (!m_isSelectingActive)
        {
            initializeSelection();
        }

        if (m_selIndex > 0)
        {
            --m_selIndex;
            m_currentCaretPosition = m_selIndex;
        }
    }

    void EditBox::selectToWordStartIndex(std::size_t wordStartingIndex)
    {
        if (!m_isSelectingActive)
        {
            initializeSelection();
        }
        m_selIndex = wordStartingIndex;
        m_isSelectingActive = true;
        updateSelectionPosition();
    }

    void EditBox::moveAndSelectByOne(sf::Keyboard::Key arrowKey)
    {
        if (!m_isSelectingActive)
        {
            initializeSelection();
        }
        if (arrowKey == sf::Keyboard::Right && m_selIndex < m_textString.length())
        {
            ++m_selIndex;
            m_currentCaretPosition = m_selIndex;
        }
        else if (arrowKey == sf::Keyboard::Left && m_selIndex > 0)
        {
            --m_selIndex;
            m_currentCaretPosition = m_selIndex;
        }
    }

    void EditBox::onEvent(EventRoot& sender, MouseButtonDownEvent& ev)
    {
        auto clickedXPosition = ev.position.x;
        auto positionOfRight = m_text.getGlobalBounds().left + m_text.getGlobalBounds().width;
        switch (ev.button)
        {
        case sf::Mouse::Button::Left:		
            moveCaretToClickedPostion(clickedXPosition, positionOfRight);

            initializeSelection();
            m_isSelecting = true;
            m_isSelectingActive = true;
            updateSelectionPosition();
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
            //onClick(ev);
            emitEvent(ev);
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
                    auto currentIndexOfLetter = findIndexOfPointedCharacter(clickedXPosition);
                    m_currentCaretPosition = currentIndexOfLetter;
                    m_selIndex = currentIndexOfLetter;
                }
                else
                {
                    m_currentCaretPosition = m_textString.length();
                    m_selIndex = m_textString.length();

                }
                clearPositionAndDistanceToLetters();
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
        KeyDownEvent keyClickedEv{};
        keyClickedEv.timestamp = ev.timestamp;
        keyClickedEv.key = ev.key;
        keyClickedEv.alt = ev.alt;
        keyClickedEv.control = ev.control;
        keyClickedEv.shift = ev.control;
        keyClickedEv.system = ev.system;
        emitEvent<KeyDownEvent>(keyClickedEv);
    }

    void EditBox::deleteCharacterAt(std::size_t indexOfCharacter)
    {
        if (!m_textString.empty())
        {
            m_textString.erase(indexOfCharacter, 1);
        }
        m_text.setString(m_textString);
        updateWordIndices();
        initializeSelection();
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

    void EditBox::deleteSelected()
    {
        eraseSelectedFromString();
        initializeSelection();
        updateWordIndices();
        m_text.setString(m_textString);
        m_isSelectingActive = false;
    }

    void EditBox::moveCaretToClickedPostion(float clickedXPosition, float positionOfRightBound)
    {
        if (clickedXPosition < positionOfRightBound)
        {
            m_currentCaretPosition = findIndexOfPointedCharacter(clickedXPosition);
            clearPositionAndDistanceToLetters();
        }
        else
        {
            m_currentCaretPosition = m_textString.length();
        }
        updateCaretPosition();
    }

    void EditBox::updateCaretPosition()
    {
        auto positinOfFirstletter = m_text.findCharacterPos(m_currentCaretPosition);
        m_caret.setPosition(positinOfFirstletter.x - 1, positinOfFirstletter.y);
    }

    void EditBox::updateWordIndices()
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
        m_indexesOfWordStarting = tempIndexes;
    }

    std::size_t EditBox::findIndexOfPointedCharacter(float clickedXPosition)
    {
        for (std::size_t i = 0; i < m_textString.length(); ++i)
        {
            m_positionsOfLetters.push_back(m_text.findCharacterPos(i).x);
        }
        if (m_positionsOfLetters.empty())
        {
            return m_currentCaretPosition;
        }
        for (auto position : m_positionsOfLetters)
        {
            m_distanceToLetters.push_back(std::abs(position - clickedXPosition));
        }
        return std::min_element(m_distanceToLetters.begin(),
            m_distanceToLetters.end()) - m_distanceToLetters.begin();
    }

    void EditBox::clearPositionAndDistanceToLetters()
    {
        m_positionsOfLetters.clear();
        m_distanceToLetters.clear();
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