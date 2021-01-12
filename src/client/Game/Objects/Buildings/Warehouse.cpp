#include "Warehouse.h"

namespace ire::client::objects
{
    Warehouse::Warehouse()
    {
        m_size = {3,4 };
        m_entrance = { 2,4 };
        initializeOverlay();
    }

    void Warehouse::initializeOverlay()
    {
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_plannedOverlays.push_back(initializeTile(sf::Color::Cyan, 0.1f, { true, true, true, true }));
                m_orderedOverlays.push_back(initializeTile(sf::Color::Green, 0.1f, { true, true, true, true }));
            }
        }
        m_orderedOverlays.at((m_entrance.y - 1) * m_size.x + (m_entrance.x - 1)).border->color = sf::Color::Magenta;

    }

    void Warehouse::updatePlannedOverlay(sf::Vector2i mousePosition)
    {
        m_position = mousePosition;
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_plannedOverlays.at(j * m_size.x + i).position = mousePosition - (m_entrance - sf::Vector2i(i + 1, j + 1));
            }
        }
    }

    void Warehouse::setupOrderedOverlay(sf::Vector2i clickPosition)
    {
        m_position = clickPosition;
        for (int i = 0; i < m_size.x; ++i)
        {
            for (int j = 0; j < m_size.y; ++j)
            {
                m_orderedOverlays.at(j * m_size.x + i).position = clickPosition - (m_entrance - sf::Vector2i(i + 1, j + 1));
            }
        }
    }

    void Warehouse::setupInProductionOverlay()
    {

    }

    void Warehouse::setupIdleOverlay()
    {

    }

}