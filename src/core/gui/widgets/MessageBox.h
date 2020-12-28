
#include "Container.h"

namespace ire::core::gui
{
    struct MessageBox : Container
    {
        MessageBox();

        static std::unique_ptr<MessageBox> create(const std::string& title = "");

        void processMessageBox();

        void setTitle(const std::string& title);
        const std::string getTitle() const;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    protected:
        std::string m_title;
        sf::Window m_window;
    };
}