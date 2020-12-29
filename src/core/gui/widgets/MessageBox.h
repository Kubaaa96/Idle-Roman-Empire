#include "Group.h"
#include "core/gui/SystemWindow.h"
#include "VerticalLayout.h"
#include "HorizontalLayout.h"

namespace ire::core::gui
{
    struct MessageBox : SystemWindow
    {
        MessageBox();

        static std::unique_ptr<MessageBox> create(const std::string& title = "");

        void processMessageBox();

        void setTitle(const std::string& title);
        const std::string getTitle() const;

        void initializeUI(std::unique_ptr<Group> group);

        static const WidgetType m_type;
        const WidgetType getType() const 
        {
            return m_type;
        }

    protected:

        std::string m_title;
        std::unique_ptr<Group> m_group;
    };
}