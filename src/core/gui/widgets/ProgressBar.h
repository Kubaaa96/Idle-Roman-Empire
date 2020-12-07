#ifndef IRE_PROGRESSBAR_H
#define IRE_PROGRESSBAR_H

#include "ClickableWidget.h"

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

        void setText(std::string& text);
        const std::string getText() const;

        void setTextSize(unsigned int textSize);
        const unsigned int getTextSize() const;

        void setFillDirection(FillDirection fillDirection);
        const FillDirection getFillDirection() const;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

    private:
        sf::RectangleShape m_rectangleShape;
        unsigned int m_minimum{ 0 };
        unsigned int m_maximum{ 100 };
        unsigned int m_value{ 0 };
        std::string m_textString;
        unsigned int m_textSize{ 15 };
        FillDirection m_fillDirection = FillDirection::LeftToRight;
        
    };
    
}
#endif //!IRE_PROGRESSBAR_H