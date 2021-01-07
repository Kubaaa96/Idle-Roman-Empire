#include "Building.h"

namespace ire::client::objects
{
    Building::Building()
    {
        initializeOverlay();
    }

    void Building::draw(sf::RenderTarget& target)
    {
        switch (m_state)
        {
        case States::Planned:

        default:
            break;
        }
    }

    const Building::States Building::getState() const
    {
        return m_state;
    }

    core::world::TileOverlay Building::updateOverlay()
    {
        switch (m_state)
        {
        case States::Planned:
            setupPlannedOverlay();
            return m_plannedOverlay;
        case States::Ordered:
            setupOrderedOverlay();
            return m_orderedOverlay;
        case States::InProduction:
            setupInProductionOverlay();
            return m_inProductionOverlay;
        case States::Idle:
            setupIdleOverlay();
            return m_idleOverlay;
        default:
            break;
        }
    }

}