#ifndef EDITBOX_H
#define EDITBOX_H

#include "ClickableWidget.h"

namespace ire::core::widgets
{
    struct EditBox : ClickableWidget
    {
        EditBox();

        static std::unique_ptr<EditBox> create(const std::string& text = "");

        void setSize(const sf::Vector2f& size) override;

        void draw(sf::RenderTarget& window) const override;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    };
}

#endif // !EDITBOX_H