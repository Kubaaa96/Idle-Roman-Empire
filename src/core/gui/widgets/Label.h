#ifndef LABEL_H
#define LABEL_H

#include "ClickableWidget.h"

namespace ire::core::gui
{

    struct Label : ClickableWidget
    {
        Label();

        static std::unique_ptr<Label> create(const std::string& text = "");

        void draw(sf::RenderTarget& target) override;

        void updateWidget() override;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    private:
        sf::RectangleShape m_rectangleShape;
    };
}
#endif // !LABEL_H