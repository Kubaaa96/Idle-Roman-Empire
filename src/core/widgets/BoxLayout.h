#ifndef BOXLAYOUT_H
#define BOXLAYOUT_H

#include "Group.h"
#include "Margins.h"

namespace ire::core::widgets
{
    struct BoxLayout : Group
    {
        BoxLayout(const sf::Vector2f& size);
        
        void setSize(const sf::Vector2f& size, bool updateWidget = true) override;
        void setPosition(const sf::Vector2f& position, bool updateWidget = true) override;

        void add( std::unique_ptr<Widget> widgetPtr, const std::string& widgetName) override;

        virtual void insert(std::size_t index, std::unique_ptr<Widget> widgetPtr, const std::string& widgetName);
        
        [[nodiscard]] bool remove(const std::string& widgetName) override;

        void setMargins(const Margins& margins);
        const Margins& getMargins() const;

        void setSpaces(float spaces);
        const float getSpaces();

        void setLayoutStretch(std::initializer_list<int> list);
        const std::vector<int> getLayoutStretch() const;

    protected:
        virtual void updateWidgets() = 0;
        bool isLayoutStretchValid();
        std::vector<int> m_layoutStretch;
        int m_sumOfLayoutStretches{ 0 };

        // SpaceBetweenWidgets
        float m_spaces{1};

        Margins m_margins;
    };
}
#endif // !BOXLAYOUT_H
