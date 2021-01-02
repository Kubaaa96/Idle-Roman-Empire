#ifndef IRE_PAWN_H
#define IRE_PAWN_H

#include "Object.h"

namespace ire::client::objects
{
    struct Pawn : Object
    {
        enum struct States
        {
            Idle,
            Moving,
            Retreating,
            LookingForShalter,
            Attacking,
            
        };
    protected:
        std::string m_nickname;
        // Hunger
        // Destination
        bool m_isCitizen;
        // Ability Experiences
    };
}

#endif //!IRE_PAWN_H
