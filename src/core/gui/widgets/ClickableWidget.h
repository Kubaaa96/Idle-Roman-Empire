#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include "Widget.h"

namespace ire::core::gui
{    
    struct ClickableWidget : Widget
    {
        ClickableWidget();

        void setSize(const sf::Vector2f& size) override;
        void setPosition(const sf::Vector2f& position) override;

        void draw(sf::RenderTarget& target)override;

        virtual void updateWidget() = 0;

        static const WidgetType m_type;

        const WidgetType getType() const override
        {
            return m_type;
        }

        void onEvent(EventRoot& sender, MouseButtonDownEvent& ev) override;

    private:
        
    };
}


#endif // !CLICKABLEWIDGET_H
