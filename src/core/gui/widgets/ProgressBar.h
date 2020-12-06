#ifndef IRE_PROGRESSBAR_H
#define IRE_PROGRESSBAR_H

#include "ClickableWidget.h"

namespace ire::core::gui
{
    struct ProgressBar : ClickableWidget
    {
        ProgressBar();

        static std::unique_ptr<ProgressBar> create(const std::string& text = "");

        void draw(sf::RenderTarget& target) override;

        void updateWidget() override;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    private:
        sf::RectangleShape m_rectangleShape;
    };
    
}
#endif //!IRE_PROGRESSBAR_H