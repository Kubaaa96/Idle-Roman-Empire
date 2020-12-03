#ifndef EDITBOX_H
#define EDITBOX_H

#include "ClickableWidget.h"

#include "core/resource/Resource.h"
#include "core/resource/FontResourceLoader.h"
#include "core/resource/ResourceManager.h"

namespace ire::core::gui
{
    enum class Alignment
    {
        Left,
        Right,
        Center
    };
    struct EditBox : ClickableWidget
    {
        EditBox();

        static std::unique_ptr<EditBox> create(const std::string& text = "");

        void draw(sf::RenderTarget& target) override;

        void updateWidget() override;

        void setTextString(const std::string& string);
        const std::string& getTextString() const;

        void setCharacterSize(unsigned int characterSize);
        const unsigned int getCharacterSize() const;

        void setGhostTextString(const std::string& string);
        const std::string getGhostTextString() const;

        void setCaretPosition(std::size_t charactersBeforeCaret);
        const std::size_t getCaretPosition() const;

        void setReadOnly(bool readOnly = true);
        bool isReadOnly() const;

        void setAlignment(Alignment alignment);
        const Alignment getAlignment() const;

        void setMaximumCharacters(unsigned int maxChars);
        const unsigned int getMaximumCharacters() const;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

        void onEvent(EventRoot& sender, TextEnteredEvent& ev) override;
        void onEvent(EventRoot& sender, KeyDownEvent& ev) override;
        void onEvent(EventRoot& sender, MouseButtonDownEvent& ev) override;
        void onEvent(EventRoot& sender, MouseButtonUpEvent& ev) override;
        void onEvent(EventRoot& sender, MouseMovedEvent& ev) override;

    protected:
        void onTextChanged(TextEnteredEvent& ev);
        void onKeyClicked(KeyDownEvent& ev);

    private:
        sf::RectangleShape m_rectangleShape;

        bool isActive = false;

        void deleteOneLetterBeforeCaret();

        void deleteOneLetterAfterCaret();

        void eraseSelectedFromString();

        unsigned int m_characterSize{ 15 };

        std::string m_textString;
        sf::Text m_text;
        std::string m_ghostTextString;
        sf::Text m_ghostText;

        sf::RectangleShape m_caret;
        bool m_caretVisible = true;
        std::size_t m_currentCaretPosition{ 0 };
        void updateCaretPosition();

        bool m_readOnly = false;

        // Zero mean no limit
        unsigned int m_maxChars = 0;

        Alignment m_textAlignment{ Alignment::Left };

        std::vector<std::size_t> m_indexesOfWordStarting{};
        void updateIndexesOfWordStarting();

        std::size_t findIndexOfLetterUnderMouse(float clickedXPosition);

        std::vector<float> m_positionsOfLetters{};
        std::vector<float> m_distanceToLetters{};
        void clearPositionAndDistanceToLetters();

        std::size_t m_selStarting{ 0 };
        std::size_t m_selIndex{ 0 };

        std::string m_selectedString;
        bool m_isSelecting = false;
        bool m_isSelectingActive = false;
        void initializeSelection();
        void updateSelectionPosition();

        sf::RectangleShape m_selection;

        ResourcePtr<sf::Font> m_font;
    };

    struct TextChangedEvent : TranslatedEvent
    {
        char32_t character;
    };

    struct KeyPressedEvent : TranslatedEvent
    {
        sf::Keyboard::Key key;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

}

#endif // !EDITBOX_H