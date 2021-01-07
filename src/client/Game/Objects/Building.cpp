#include "Building.h"

namespace ire::client::objects
{
    Building::Building()
    {
        initializeOverlay();
    }

    void Building::setState(States state)
    {
        if (m_state != state)
        {
            m_state = state;
        }
    }

    const Building::States Building::getState() const
    {
        return m_state;
    }

    const core::world::TileOverlay Building::getPlannedOverlay() const
    {
        return m_plannedOverlay;
    }

    const core::world::TileOverlay Building::getOrderedOverlay() const
    {
        return m_orderedOverlay;
    }

}