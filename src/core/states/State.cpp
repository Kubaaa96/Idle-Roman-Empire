#include "State.h"

namespace ire::core::state
{
    State::State(const sf::Vector2u sizeOfWindow)
        : m_sizeOfWindow(static_cast<sf::Vector2f>(sizeOfWindow))
    {
    }
}