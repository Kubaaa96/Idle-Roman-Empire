#include "Road.h"

namespace ire::client::objects
{
    Road::Road()
    {
        initializeOverlay();
    }

    void Road::initializeOverlay()
    {
        m_plannedOverlays.push_back(initializeTile(sf::Color::Cyan, 0.1f, { true, true, true, true }));
        m_orderedOverlays.push_back(initializeTile(sf::Color::Blue, 0.1f, { true, true, true, true }));
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