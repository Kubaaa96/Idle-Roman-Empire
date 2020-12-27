#ifndef BUTTON_H
#define BUTTON_H

#include "ClickableWidget.h"
#include "core/gui/Text.h"

#include "core/resource/Resource.h"
#include "core/resource/FontResourceLoader.h"
#include "core/resource/ResourceManager.h"

namespace ire::core::gui
{
    struct Button : ClickableWidget
    {
        Button();

        static std::unique_ptr<Button> create(const std::string& text = "");

        void draw(sf::RenderTarget& target)override;

        void updateWidget() override;

        void setTextString(const std::string& string);
        sf::String getTextString();

        void setCharacterSize(const unsigned int characterSize);
        const unsigned int getCharacterSize() const;

        void setTextStyle(const sf::Uint32 style);
        const sf::Uint32 getTextStyle() const;

        void setTextFillColor(const sf::Color textFillColor);
        const sf::Color getTextFillColor() const;

        void setTextOutlineColor(const sf::Color textOutlineColor);
        const sf::Color getTextOutlineColor() const;

        void setTextOutlineThickness(const float textOutlineThickness);
        const float getTextOutlineThickness() const;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

        void setVAlignment(Text::VerticalAlignment vAlign);
        const Text::VerticalAlignment getVAlignment() const;

        void setHAlignment(Text::HorizontalAlignment hAlign);
        const Text::HorizontalAlignment getHAlignment() const;

        void setAlignment(Text::VerticalAlignment vAlign, Text::HorizontalAlignment hAlign);

    private:
        void updateTextPosition();

        sf::RectangleShape m_rectangleShape;
        Text m_text;
    };
}

#endif // !BUTTON_H
