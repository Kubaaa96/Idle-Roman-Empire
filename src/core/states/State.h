#ifndef IRE_STATE_H
#define IRE_STATE_H

#include "core/gui/widgets/Group.h"

namespace ire::core::state
{
    struct State
    {
        State(const sf::Vector2u sizeOfWindow);
        virtual gui::Group* drawGUI() = 0;
    protected:
        const sf::Vector2f m_sizeOfWindow;

    };
}

#endif // !IRE_STATE_H