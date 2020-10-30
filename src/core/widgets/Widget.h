#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "WidgetType.h"

namespace ire::core::widgets
{
    struct Container;
    // Base class for all Widgets and Layouts
    struct Widget
    {
        Widget() = default;
        virtual ~Widget();

        Widget(Widget&&) = delete;
        Widget& operator=(Widget&&) = delete;

        void setWidgetName(const std::string& name);
        [[nodiscard]] std::string getWidgetName() const;

        virtual void setPosition(const sf::Vector2f& position, bool updateWidget = true);
        void setPosition(float x, float y);
        [[nodiscard]] const sf::Vector2f getPosition() const;
        void setLocalPosition(const sf::Vector2f& localPosition);
        [[nodiscard]] const sf::Vector2f getLocalPosition() const;

        virtual void setSize(const sf::Vector2f& size, bool updateWidget = true);
        void setSize(float x, float y);
        void setWidth(float width, bool updateWidget = true);
        void setHeight(float height, bool updateWidget = true);
        [[nodiscard]] sf::Vector2f getSize() const;

        void setOrigin(sf::Vector2f origin);
        void setOrigin(float x, float y);
        [[nodiscard]] sf::Vector2f getOrigin() const;

        virtual void draw(sf::RenderTarget& target) = 0;

        virtual void setParent(Container* parent);
        [[nodiscard]] Container* getParent() const;
        
        virtual const WidgetType getType() const = 0;

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
