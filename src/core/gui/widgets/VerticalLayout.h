#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include "BoxLayout.h"
#include "Margins.h"

namespace ire::core::gui
{
    struct VerticalLayout : BoxLayout
    {
        VerticalLayout(const sf::Vector2f& size);

        static std::unique_ptr<VerticalLayout> create(const sf::Vector2f& size);

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    protected:
        void updateWidgets() override;
    };
}

#endif // !VERTICALLAYOUT_H
