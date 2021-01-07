#include "Road.h"

namespace ire::client::objects
{
    Road::Road()
    {
        initializeOverlay();
    }

    void Road::initializeOverlay()
    {
        m_plannedOverlay.border = core::world::TileOverlayBorder{};
        //m_plannedOverlay.position = sf::Vector2i(255,256);
        m_plannedOverlay.border->color = sf::Color::Cyan;
        m_plannedOverlay.border->thickness = 0.1f;
        m_plannedOverlay.border->visible = { true, true, true, true };

        m_orderedOverlay.border = core::world::TileOverlayBorder{};
        m_orderedOverlay.border->color = sf::Color::Cyan;
        m_orderedOverlay.border->thickness = 1.f;
        m_orderedOverlay.border->visible = { true, true, true, true };
    }

    void Road::updatePlannedOverlay(sf::Vector2i mousePosition)
    {
        m_plannedOverlay.position = mousePosition;
    }

    void Road::setupOrderedOverlay(sf::Vector2i clickPosition)
    {
        m_orderedOverlay.position = clickPosition;
    }

    void Road::setupInProductionOverlay()
    {

    }

    void Road::setupIdleOverlay()
    {

    }
}