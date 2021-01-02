#ifndef IRE_BUILDING_H
#define IRE_BUILDING_H

#include "Object.h"

namespace ire::client::objects
{
    struct Building : Object
    {
        enum struct States
        {
            Null,
            Planned,
            Ordered,
            InProduction,
            Idle,
            Working,
            Full,
            Demaged
        };
    protected:
        // Needed Workers
        // Curent Workers
        States m_state = States::Null;
        // Size
        // Entrances

    };
}

#endif //!IRE_BUILDING_H