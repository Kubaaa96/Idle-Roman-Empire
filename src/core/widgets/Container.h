#ifndef CONTAINER_H
#define CONTAINER_H

#include "Widget.h"

#include <vector>

namespace ire::core::widgets
{
    // Base container class for grouping widgets
    struct Container : Widget
    {
        Container() = default;
        ~Container() = default;
        Container(Container& other) = delete;
        Container(Container&& other) = delete;
        
        Container& operator=(Container& other) = delete;
        Container& operator=(Container&& other) = delete;

        void setSize(const sf::Vector2f& size) override;

        [[nodiscard]] const std::vector<std::unique_ptr<Widget>>& getWidgets() const;

        // Widget Name Should not contain whitespaces
        virtual void add(const std::unique_ptr<Widget>& widgetPtr, const std::string& widgetName = "");


        [[nodiscard]] virtual bool remove(const std::unique_ptr<Widget>& widgetPtr);

        virtual void removeAllWidgets();

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
    };
}
#endif // !CONTAINER_H