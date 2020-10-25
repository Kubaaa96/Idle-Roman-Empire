#ifndef CONTAINER_H
#define CONTAINER_H

#include "Widget.h"

#include <vector>
#include <iostream>

namespace ire::core::widgets
{
    // Base container class for grouping widgets
    struct Container : Widget
    {
        Container();
        ~Container() = default;
        Container(Container& other) = delete;
        Container(Container&& other) = delete;
        
        Container& operator=(Container& other) = delete;
        Container& operator=(Container&& other) = delete;

        void setSize(const sf::Vector2f& size) override;

        virtual sf::Vector2f getInnerSize() const;

        [[nodiscard]] const std::vector<std::unique_ptr<Widget>>& getWidgets() const;

        // Widget Name Should not contain whitespaces
        virtual void add( std::unique_ptr<Widget> widgetPtr, const std::string& widgetName);

        [[nodiscard]] bool remove(const std::string& widgetName);

        Widget* get(int index);

        const Widget* get(int index) const;
        
        Widget* get(const std::string name);
        const Widget* get(const std::string name) const;

        void draw(sf::RenderTarget& window) const override;

        WidgetType getType() const override;

    protected:
        std::vector<std::unique_ptr<Widget>> m_widgets;

    private:
        std::unique_ptr<Widget> clone() const override
        {
            return nullptr;
        }

        static WidgetType m_type;

        bool compareWithWidgetNameAt(std::size_t index, const std::string& name);
        const bool compareWithWidgetNameAt(std::size_t index, const std::string& name) const;
        Widget* getWidgetAt(int i);
        const Widget* getWidgetAt(int i) const;
    };
}
#endif // !CONTAINER_H
