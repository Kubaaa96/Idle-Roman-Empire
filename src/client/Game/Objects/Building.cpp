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

    std::vector<core::world::TileOverlay> Building::getPlannedOverlay() const
    {
        return m_plannedOverlays;
    }

    std::vector<core::world::TileOverlay> Building::getOrderedOverlay() const
    {
        return m_orderedOverlays;
    }

}