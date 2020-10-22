#ifndef CONTAINER_H
#define CONTAINER_H

#include "Widget.h"

#include <vector>

namespace ire::core::widgets
{
    struct Container : Widget
    {
        Container();
        ~Container();
        Container(Container&& other) noexcept;
        Container& operator=(Container&& other) noexcept;

        void setSize(const sf::Vector2f& size) override;

        [[nodiscard]] const std::vector<std::unique_ptr<Widget>>& getWidgets() const;

        // Widget Name Should not contain whitespaces
        virtual void add(const std::unique_ptr<Widget>& widgetPtr, const std::string& widgetName = "");

        [[nodiscard]] virtual bool remove(const std::unique_ptr<Widget>& widgetPtr);

        virtual void removeAllWidgets();

        [[nodiscard]] virtual std::unique_ptr<Widget> getWidgetAtPosition(sf::Vector2f pos) const;

        void draw(sf::RenderWindow& window) const override;


        template<typename Function>
        void sortWidgets(Function&& function)
        {
            std::sort(m_widgets.begin(), m_widgets.end(), std::forward<Function>(function));
        }


        [[nodiscard]] std::unique_ptr<Widget> get(const std::string& widgetName) const;

        template<typename T>
        [[nodiscard]] std::unique_ptr<T> get(const std::string& widgetName) const
        {
            return std::dynamic_pointer_cast<T>(get(widgetName));
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