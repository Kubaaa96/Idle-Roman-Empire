#ifndef WIDGET_H
#define WIDGET_H

#include "WidgetType.h"

#include "core/gui/Events.h"
#include "core/gui/EventRoot.h"
#include "core/gui/RawEventHandler.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace ire::core::gui
{
    struct Container;
    // Base class for all Widgets and Layouts
    struct Widget : RawEventHandler
    {
        Widget() = default;
        virtual ~Widget();

        Widget(Widget&&) = delete;
        Widget& operator=(Widget&&) = delete;

        void setWidgetName(const std::string& name);
        [[nodiscard]] std::string getWidgetName() const;

        virtual void setPosition(const sf::Vector2f& position);
        [[nodiscard]] sf::Vector2f getPosition() const;
        virtual void setLocalPosition(const sf::Vector2f& localPosition);
        [[nodiscard]] sf::Vector2f getLocalPosition() const;

        virtual void setSize(const sf::Vector2f& size);
        void setWidth(float width);
        void setHeight(float height);
        [[nodiscard]] sf::Vector2f getSize() const;

        void setOrigin(sf::Vector2f origin);
        [[nodiscard]] sf::Vector2f getOrigin() const;

        virtual void draw(sf::RenderTarget& target) = 0;

        virtual void setParent(Container* parent);
        [[nodiscard]] Container* getParent() const;
        
        virtual const WidgetType getType() const = 0;

        [[nodiscard]] sf::FloatRect clientBounds() const;

        virtual void onStoppedBeingActive();

    protected:
        std::string m_name;

        sf::Vector2f m_localPosition;
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::Vector2f m_origin;

        Container* m_parent = nullptr;
    };
}
#endif // !WIDGET_H
