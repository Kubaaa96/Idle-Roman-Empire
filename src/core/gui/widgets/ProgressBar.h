#ifndef IRE_PROGRESSBAR_H
#define IRE_PROGRESSBAR_H

#include "ClickableWidget.h"

#include "core/resource/Resource.h"
#include "core/resource/FontResourceLoader.h"
#include "core/resource/ResourceManager.h"
#include "core/gui/CollectionOfEvents.h"

namespace ire::core::gui
{
    struct ProgressBar : ClickableWidget
    {
        enum class FillDirection
        {
            LeftToRight,
            RightToLeft,
            TopToBottom,
            BottomToTop,
            // CounterClockwise,
            // Clockwise
        };

        ProgressBar();

        static std::unique_ptr<ProgressBar> create(const std::string& text = "");

        void draw(sf::RenderTarget& target) override;

        void updateWidget() override;

        void setMinimum(unsigned int minimum);
        const unsigned int getMinimum() const;

        void setMaximum(unsigned int maximum);
        const unsigned int getMaximum() const;

        void setValue(unsigned int value);
        const unsigned int getValue() const;

        void setTextString(std::string& text);
        const std::string getTextString() const;

        void setTextSize(unsigned int textSize);
        const unsigned int getTextSize() const;

        void setTextFillColor(sf::Color textColor);
        const sf::Color getTextFillColor() const;

        void setTextStyle(sf::Uint32 textStyle);
        const sf::Uint32 getTextStyle() const;

        void setFillDirection(FillDirection fillDirection);
        const FillDirection getFillDirection() const;

        void setCharacterSize(unsigned int characterSize);
        const unsigned int getCharacterSize() const;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

        void onEvent(EventRoot& sender, KeyDownEvent& ev) override;
    protected:
        void onKeyClicked(KeyDownEvent& ev);

    private:
        sf::RectangleShape m_rectangleShape;
        sf::RectangleShape m_progressShape;
        unsigned int m_minimum{ 200 };
        unsigned int m_maximum{ 600 };
        unsigned int m_value{ 400 };
        float calculatedPercent();
        std::string m_textString;
        unsigned int m_textSize{ 15 };
        sf::Text m_textMain;
        sf::Text m_textMinimum;
        sf::Text m_textMaximum;
        ResourcePtr<sf::Font> m_font;
        void updateTextPosition();
        void updateTextString();
        void updateFillDirection();
        void invertBarsColors();
        FillDirection m_fillDirection = FillDirection::RightToLeft;
        
    };

}
#endif //!IRE_PROGRESSBAR_H