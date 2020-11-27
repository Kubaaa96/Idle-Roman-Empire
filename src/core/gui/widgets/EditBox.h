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

        void draw(sf::RenderTarget& target)override;

        void updateWidget() override;

        void setTextString(const std::string& string);
        const std::string getTextString() const;

        void setGhostTextString(const std::string& string);
        const std::string getGhostTextString() const;

        void setCaretPosition(std::size_t charactersBeforeCaret);
        const std::size_t getCaretPosition() const;

        void setReadOnly(bool readOnly = true);
        bool isReadOnly() const;

        void setTextSize(unsigned int textSize);
        const unsigned int getTextSize() const;

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

    protected:
        void onTextChanged(TextEnteredEvent& ev);

    private:
        sf::RectangleShape m_rectangleShape;

        void backspaceKeyPressed();

        void deleteKeyPressed();

        std::string m_stringText;
        sf::Text m_text;
        sf::String m_textString;
        sf::String m_ghostTextString;

        sf::RectangleShape m_caret;
        int m_caretCounter = 0;
        const int m_caretBlinkingFrequency = 30;
        bool m_caretVisible = true;

        bool m_readOnly = false;

        // Zero mean no limit
        unsigned int m_maxChars = 0;

        Alignment m_textAlignment{ Alignment::Left };

        ResourcePtr<sf::Font> m_font;
    

    };

    struct TextChangedEvent : TranslatedEvent
    {
        char32_t characters;
    };
}

#endif // !EDITBOX_H