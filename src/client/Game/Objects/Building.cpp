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

    core::world::TileOverlay Building::initializeTile(sf::Color borderColor, float borderThickness, core::util::FourWay<bool> borderVisibility)
    {
        auto overlay = core::world::TileOverlay();
        overlay.border = core::world::TileOverlayBorder{};
        overlay.border->color = borderColor;
        overlay.border->thickness = borderThickness;
        overlay.border->visible = borderVisibility;
        return overlay;
    }

}