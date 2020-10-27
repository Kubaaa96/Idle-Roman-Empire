#ifndef LABEL_H
#define LABEL_H

#include "ClickableWidget.h"

namespace ire::core::widgets
{

    struct Label : ClickableWidget
    {
        Label();

        static std::unique_ptr<Label> create(const std::string& text = "");

        void setSize(const sf::Vector2f& size) override;

        void draw(sf::RenderTarget& target) const override;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    };
}
#endif // !LABEL_H