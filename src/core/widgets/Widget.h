#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace ire::core::widgets
{
    // Base class for all Widgets and Layouts
    struct Widget
    {
        Widget();
        Widget(Widget&&) noexcept;
        virtual ~Widget();

        Widget& operator=(Widget&&) noexcept;

        void setWidgetName(const std::string& name);
        std::string getWidgetName() const;

        virtual void setPosition(const sf::Vector2f& position);
        void setPosition(float x, float y);
        sf::Vector2f getPosition() const;

        virtual void setSize(const sf::Vector2f& size);
        void setSize(float x, float y);
        void setWidth(float width);
        void setHeigh(float height);
        sf::Vector2f getSize() const;

        void setOrigin(sf::Vector2f origin);
        void setOrigin(float x, float y);
        sf::Vector2f getOrigin() const;

        // Temp for testing 
        void drawRect(sf::RenderWindow& window);

    private:
        std::string m_type;
        std::string m_name;

        sf::Vector2f m_position;
        sf::Vector2f m_size;
        sf::Vector2f m_origin;

        std::unique_ptr<Widget> m_parent = nullptr;

    };
}
#endif // WIDGET_H