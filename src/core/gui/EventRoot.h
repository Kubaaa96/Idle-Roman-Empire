#ifndef IRE_EVENT_ROOT_H
#define IRE_EVENT_ROOT_H

namespace ire::core::gui {

    struct Widget;

    struct EventRoot
    {
        virtual void setActiveWidget(Widget& widget) = 0;
        virtual void resetActiveWidget() = 0;
    };

}

#endif // !IRE_EVENT_ROOT_H
