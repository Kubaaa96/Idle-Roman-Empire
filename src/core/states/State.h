#ifndef IRE_STATE_H
#define IRE_STATE_H

namespace ire::core::state
{
    struct State
    {
        virtual void drawGUI() = 0;
        
    };
}

#endif // !IRE_STATE_H