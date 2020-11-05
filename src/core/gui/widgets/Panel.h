#ifndef PANEL_H
#define PANEL_H

#include "Group.h"
#include "Widget.h"
#include "BoxLayout.h"

namespace ire::core::gui
{

    struct Panel : Widget
    {
        Panel(const sf::Vector2f& size, std::unique_ptr<BoxLayout> mainPanelLayout, const std::string& layoutName);
        static std::unique_ptr<Panel> create(const sf::Vector2f size, 
            std::unique_ptr<BoxLayout> mainPanelLayout, const std::string& layoutName);
        void setSize(const sf::Vector2f& size) override;
        void setPosition(const sf::Vector2f& position)override;

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

        void onEvent(EventRoot& sender, MouseButtonDownEvent& ev) override;
        void onEvent(EventRoot& sender, MouseButtonUpEvent& ev) override;
        void onEvent(EventRoot& sender, MouseMovedEvent& ev) override;

    protected:
        std::unique_ptr<BoxLayout> m_panelLayout;
    private:
        void updateLayout();
        sf::RectangleShape m_rectangleShape;

        template <typename EventT>
        void forwardEvent(EventRoot& sender, EventT& ev)
        {
            m_panelLayout->onEvent(sender, ev);

            Widget::onEvent(sender, ev);
        }
    };
}


#endif //!PANEL_H