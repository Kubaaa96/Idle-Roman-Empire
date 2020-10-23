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


        void draw(sf::RenderWindow& window) const override;
    };
}


#endif // !CLICKABLEWIDGET_H