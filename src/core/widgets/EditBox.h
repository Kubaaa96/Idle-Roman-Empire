#ifndef EDITBOX_H
#define EDITBOX_H

#include "ClickableWidget.h"

namespace ire::core::widgets
{
    struct EditBox : ClickableWidget
    {
        EditBox();

        static std::unique_ptr<EditBox> create(const std::string& text = "");

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

#endif // !EDITBOX_H