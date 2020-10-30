#ifndef PANEL_H
#define PANEL_H

#include "Group.h"
#include "Widget.h"
#include "BoxLayout.h"

namespace ire::core::widgets
{

    struct Panel : Widget
    {
        Panel(const sf::Vector2f& size, std::unique_ptr<BoxLayout> mainPanelLayout, const std::string& layoutName);
        static std::unique_ptr<Panel> create(const sf::Vector2f size, 
            std::unique_ptr<BoxLayout> mainPanelLayout, const std::string& layoutName);
        void setSize(const sf::Vector2f& size, bool updateWidget = true) override;
        void setPosition(const sf::Vector2f& position, bool updateWidget = true)override;

        [[nodiscard]] const std::unique_ptr<BoxLayout>& getLayout() const;

        void draw(sf::RenderTarget& target) override;

        void setBackgroundColor(const sf::Color backgroundColor);
        [[nodiscard]] const sf::Color getBackgroundColor() const;

        void setOpacity(std::uint8_t alpha);
        [[nodiscard]] const std::uint8_t getOpacity() const;

        void setOutlineColor(const sf::Color outlineColor);
        [[nodiscard]] const sf::Color getOutlineColor() const;

        void setOutlineThickness(float thickness);
        [[nodiscard]] const float getOutlineThickness() const;

        static const WidgetType m_type;
        [[nodiscard]] const WidgetType getType() const override
        {
            return m_type;
        }

    protected:
        std::unique_ptr<BoxLayout> m_panelLayout;
    private:
        void updateLayout();
        sf::RectangleShape m_rectangleShape;
    };
}


#endif //!PANEL_H