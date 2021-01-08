#include "Road.h"

namespace ire::client::objects
{
    Road::Road()
    {
        initializeOverlay();
    }

    void Road::initializeOverlay()
    {
        auto plannedOverlay = core::world::TileOverlay();
        plannedOverlay.border = core::world::TileOverlayBorder{};
        plannedOverlay.border->color = sf::Color::Cyan;
        plannedOverlay.border->thickness = 0.1f;
        plannedOverlay.border->visible = { true, true, true, true };
        m_plannedOverlays.push_back(plannedOverlay);

        auto orderedOverlay = core::world::TileOverlay();
        orderedOverlay.border = core::world::TileOverlayBorder{};
        orderedOverlay.border->color = sf::Color::Blue;
        orderedOverlay.border->thickness = 0.1f;
        orderedOverlay.border->visible = { true, true, true, true };
        m_orderedOverlays.push_back(orderedOverlay);
    }

    void Road::updatePlannedOverlay(sf::Vector2i mousePosition)
    {
        m_plannedOverlays.begin()->position = mousePosition;
        m_currentPosition = mousePosition;
    }

    void Road::setupOrderedOverlay(sf::Vector2i clickPosition)
    {
        m_orderedOverlays.begin()->position = clickPosition;
        m_currentPosition = clickPosition;
    }

    void Road::setupInProductionOverlay()
    {

    }

    void Road::setupIdleOverlay()
    {

    }
}