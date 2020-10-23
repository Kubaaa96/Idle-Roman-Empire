#ifndef CONTAINER_H
#define CONTAINER_H

#include "Widget.h"

#include <vector>

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

        bool remove(const std::string& widgetName);

        std::unique_ptr<Widget> &get(int index);
        
        std::unique_ptr<Widget>& get(const std::string& name);

        void draw(sf::RenderWindow& window) const override;


        template<typename Function>
        void sortWidgets(Function&& function)
        {
            std::sort(m_widgets.begin(), m_widgets.end(), std::forward<Function>(function));
        }

    protected:
        std::vector<std::unique_ptr<Widget>> m_widgets;

    private:
        std::unique_ptr<Widget> clone() const override
        {
            return nullptr;
        }
        bool compareWithWidgetNameAt(std::size_t index, const std::string& name);
    };
}
#endif // !CONTAINER_H