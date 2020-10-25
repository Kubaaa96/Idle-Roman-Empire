#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include "Widget.h"


namespace ire::core::widgets
{    
    struct ClickableWidget : Widget
    {
        ClickableWidget();
        std::unique_ptr<ClickableWidget> create(sf::Vector2f size);

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


#endif // !CLICKABLEWIDGET_H