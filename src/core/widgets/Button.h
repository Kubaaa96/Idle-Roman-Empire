#ifndef BUTTON_H
#define BUTTON_H

#include "ClickableWidget.h"

namespace ire::core::widgets
{
    struct Button : ClickableWidget
    {
        Button();

        static std::unique_ptr<Button> create(const std::string& text = "");

        void setSize(const sf::Vector2f& size) override;

        std::unique_ptr<Widget> clone() const override;

        void draw(sf::RenderTarget& window) const override;

        WidgetType getType() const override
        {
            return m_type;
        }

    private:
        static WidgetType m_type;
    };
}

#endif // !BUTTON_H