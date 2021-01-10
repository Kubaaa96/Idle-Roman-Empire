#include "Warehouse.h"

namespace ire::client::objects
{
    Warehouse::Warehouse()
    {
        initializeOverlay();
    }
    void Warehouse::initializeOverlay()
    {
        initializePlannedOverlay();
        initializeOrderedOverlay();
    }

    void Warehouse::updatePlannedOverlay(sf::Vector2i mousePosition)
    {
        m_currentPosition = mousePosition;
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_plannedOverlays.at(j * m_size.y + i).position = mousePosition - (sf::Vector2i(2, 3) - sf::Vector2i(i, j));
            }
        }
    }

    void Warehouse::setupOrderedOverlay(sf::Vector2i clickPosition)
    {
        m_currentPosition = clickPosition;
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_orderedOverlays.at(j * m_size.y + i).position = clickPosition - (sf::Vector2i(2,3) - sf::Vector2i(i,j));
            }
        }
    }

    void Warehouse::setupInProductionOverlay()
    {

    }

    void Warehouse::setupIdleOverlay()
    {

    }

    void Warehouse::initializePlannedOverlay()
    {
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                auto plannedOverlay = core::world::TileOverlay();
                plannedOverlay.border = core::world::TileOverlayBorder{};
                plannedOverlay.border->color = sf::Color::Cyan;
                plannedOverlay.border->thickness = 0.1f;
                plannedOverlay.border->visible = { true, true, true, true };
                m_plannedOverlays.push_back(plannedOverlay);
            }
        }
    }

    void Warehouse::initializeOrderedOverlay()
    {
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                auto orderedOverlay = core::world::TileOverlay();
                orderedOverlay.border = core::world::TileOverlayBorder{};
                orderedOverlay.border->color = sf::Color::Magenta;
                orderedOverlay.border->thickness = 0.1f;
                orderedOverlay.border->visible = { true, true, true, true };
                m_orderedOverlays.push_back(orderedOverlay);
            }
        }
        m_orderedOverlays.at(14).border->color = sf::Color::Magenta;
    }
}