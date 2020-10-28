#ifndef PANEL_H
#define PANEL_H

#include "Group.h"
#include "Widget.h"
#include "BoxLayout.h"

namespace ire::core::widgets
{

    struct Panel : Widget
    {
        Panel(const sf::Vector2f& size, std::unique_ptr<BoxLayout> mainPanelLayout, std::string& layoutName);
        static std::unique_ptr<Panel> create(const sf::Vector2f size, 
            std::unique_ptr<BoxLayout> mainPanelLayout, std::string& layoutName);
        void setSize(const sf::Vector2f& size) override;
        void setPosition(const sf::Vector2f& position)override;

        void draw(sf::RenderTarget& target) override;

        void setBackground(const sf::Color backgroundColor);
        void setOpacity(std::uint8_t alpha);
        void setOutlineColor(const sf::Color outlineColor);
        void setOutlineThickness(float thickness);

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

    protected:
        sf::Color m_Outline;
        sf::Color m_Background;
        std::unique_ptr<BoxLayout> m_panelLayout;
    private:
        void updateLayout();
        sf::RectangleShape m_rectangleShape;
    };
}


#endif //!PANEL_H