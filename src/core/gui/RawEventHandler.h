#ifndef IRE_RAW_EVENT_HANDLER_H
#define IRE_RAW_EVENT_HANDLER_H

#include "EventRoot.h"
#include "Events.h"

namespace ire::core::gui {

    struct RawEventHandler : EventEmitter
    {
        virtual void onEvent(EventRoot& sender, MouseButtonDownEvent& ev);
    };

}

#endif // !IRE_RAW_EVENT_HANDLER_H
