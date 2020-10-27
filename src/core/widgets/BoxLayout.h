#ifndef BOXLAYOUT_H
#define BOXLAYOUT_H

#include "Group.h"

namespace ire::core::widgets
{
    struct BoxLayout : Group
    {
        BoxLayout(const sf::Vector2f& size);
        
        void setSize(const sf::Vector2f& size);

         void add( std::unique_ptr<Widget> widgetPtr, const std::string& widgetName) override;

         virtual void insert(std::size_t index, std::unique_ptr<Widget>& widgetPtr, const std::string& widgetName);
        
         [[nodiscard]] bool remove(const std::string& widgetName) override;

    protected:
        virtual void updateWidgets() = 0;

        // SpaceBetweenWidgets
        float m_spaces{ 0 };
        // LeftMargin
        float m_LeftMargin{ 0 };
        // RightMargin
        float m_RightMargin{ 0 };
        // TopMargin
        float m_TopMargin{ 0 };
        // BottomMargin
        float m_BottomMargin{ 0 };
    };
}
#endif // !BOXLAYOUT_H
