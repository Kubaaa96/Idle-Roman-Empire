#ifndef LABEL_H
#define LABEL_H

#include "ClickableWidget.h"
#include "core/gui/Text.h"

namespace ire::core::gui
{

    struct Label : ClickableWidget
    {
        Label();

        static std::unique_ptr<Label> create(const std::string& text = "");

        void draw(sf::RenderTarget& target) override;

        void updateWidget() override;

        void setTextString(const std::string& string);
        const std::string getTextString() const;

        void setCharacterSize(unsigned int characterSize);
        const unsigned int getCharacterSize() const;

        void setVerticalAlignment(Text::VerticalAlignment verticalAlignment);
        const Text::VerticalAlignment getVerticalAlignment() const;

        void setHorizontalAlignment(Text::HorizontalAlignment horizontalAlignment);
        const Text::HorizontalAlignment getHorizontalAlignment() const;

        void setTextVisible(bool isVisible);
        const bool isTextVisible() const;

        void setTextFillColor(sf::Color fillColor);
        const sf::Color getTextFillColor() const;

        void setTextOutlineColor(sf::Color outlineColor);
        const sf::Color getTextOutlineColor() const;

        void setTextOutlineThickness(float outlineThickness);
        const float getTextOutlineThickness() const;

        void setTextStyle(sf::Uint32 style);

        void setTextLatterSpacing(float spacingFactor);

        void setTextLineSpacing(float spacingFactor);

        void setTextFont(const std::string& pathToFont);

        void setBackgroundShapeColor(sf::Color backgroundColor);
        const sf::Color getBackgroundShapeColor() const;

        void setBackgdoungVisibility(bool isBackgroundVisible);
        const bool isBackgroundVisible() const;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    private:
        sf::RectangleShape m_backgroundShape;
        bool m_isBackgroundVisible = false;

        Text m_mainText;
        
    };
}
#endif // !LABEL_H