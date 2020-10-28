#ifndef PANEL_H
#define PANEL_H

#include "Group.h"

namespace ire::core::widgets
{
    struct Panel : Group
    {
        Panel(const sf::Vector2f& size);
        static std::unique_ptr<Panel> create(const sf::Vector2f size);
        void setSize(const sf::Vector2f& size) override;
        void draw(sf::RenderTarget& target) const override;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

    protected:
        sf::Color m_Outline;
        sf::Color m_Background;
    };
}


#endif //!PANEL_H