#ifndef IRE_COLECTIONOFEVENTS
#define IRE_COLECTIONOFEVENTS

#include "Events.h"

namespace ire::core::gui
{
    struct KeyPressedEvent : TranslatedEvent
    {
        sf::Keyboard::Key key;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };
}
#endif // !IRE_COLECTIONOFEVENTS