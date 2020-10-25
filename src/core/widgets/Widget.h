#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include <memory>
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

        virtual void setPosition(const sf::Vector2f& position);
        void setPosition(float x, float y);
        [[nodiscard]] sf::Vector2f getPosition() const;

        virtual void setSize(const sf::Vector2f& size);
        void setSize(float x, float y);
        void setWidth(float width);
        void setHeigh(float height);
        [[nodiscard]] sf::Vector2f getSize() const;

        void setOrigin(sf::Vector2f origin);
        void setOrigin(float x, float y);
        [[nodiscard]] sf::Vector2f getOrigin() const;

        virtual void draw(sf::RenderTarget& window) const = 0;

        virtual std::unique_ptr<Widget> clone() const = 0;

        virtual void setParent(Container* parent);
        [[nodiscard]] Container* getParent() const;
        
        virtual const WidgetType getType() const = 0;

        // Temp for testing 
        void drawRect(sf::RenderWindow& window);


    protected:
        std::string m_name;

        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::Vector2f m_origin;

        Container* m_parent = nullptr;

    };
}
#endif // !WIDGET_H