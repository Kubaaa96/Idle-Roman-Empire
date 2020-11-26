#ifndef BUTTON_H
#define BUTTON_H

#include "ClickableWidget.h"

#include "core/resource/Resource.h"
#include "core/resource/ResourceLoader.h"
#include "core/resource/ResourcePath.h"
#include "core/resource/FontResourceLoader.h"

namespace ire::core::gui
{
    enum struct VAlign
    {
        Left,
        Right,
        Center,
    };
    enum struct HAlign
    {
        Top,
        Bottom,
        Center,
    };

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

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

        void setVAlignment(VAlign vAlign);
        const VAlign getVAlignment() const;

        void setHAlignment(HAlign hAlign);
        const HAlign getHAlignment() const;

        void setAlignment(VAlign vAlign, HAlign hAlign);

    private:
        void updatePosition();

        sf::RectangleShape m_rectangleShape;
        sf::Text m_text;
        sf::String m_textString;
        VAlign m_vAlign;
        HAlign m_hAlign;
        detail::EagerResource<sf::Font> m_font{ "resource/RomanSD.ttf" };
    };


}

#endif // !BUTTON_H
