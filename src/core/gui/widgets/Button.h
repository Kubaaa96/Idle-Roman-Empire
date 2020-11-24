#ifndef BUTTON_H
#define BUTTON_H

#include "ClickableWidget.h"

#include "core/resource/Resource.h"
#include "core/resource/ResourceLoader.h"
#include "core/resource/ResourcePath.h"
#include "core/resource/FontResourceLoader.h"

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

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

    private:
        sf::RectangleShape m_rectangleShape;
        sf::Text m_text;
        sf::String m_textString;
        detail::EagerResource<sf::Font> m_font{ "resource/RomanSD.ttf" };
    };
}

#endif // !BUTTON_H
