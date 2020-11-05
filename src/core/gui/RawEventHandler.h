#ifndef IRE_RAW_EVENT_HANDLER_H
#define IRE_RAW_EVENT_HANDLER_H

#include "EventRoot.h"
#include "Events.h"

namespace ire::core::gui {

    struct RawEventHandler : EventEmitter
    {
        virtual void onEvent(EventRoot& sender, MouseButtonDownEvent& ev);
        virtual void onEvent(EventRoot& sender, MouseButtonUpEvent& ev);
        virtual void onEvent(EventRoot& sender, MouseMovedEvent& ev);

    };

}

#endif // !IRE_RAW_EVENT_HANDLER_H
