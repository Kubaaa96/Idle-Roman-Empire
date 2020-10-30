#ifndef BUTTON_H
#define BUTTON_H

#include "ClickableWidget.h"

namespace ire::core::widgets
{
    struct Button : ClickableWidget
    {
        Button();

        static std::unique_ptr<Button> create(const std::string& text = "");

        void draw(sf::RenderTarget& target)override;

        void updateCurrentWidget() override;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

    private:
        sf::RectangleShape m_rectangleShape;
    };
}

#endif // !BUTTON_H
