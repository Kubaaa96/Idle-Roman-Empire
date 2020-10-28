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

        static const WidgetType m_type;

        const WidgetType getType() const override
        {
            return m_type;
        }

    private:
        
    };
}


#endif // !CLICKABLEWIDGET_H
