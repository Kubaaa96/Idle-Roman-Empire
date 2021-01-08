#include "ObjectMenager.h"

namespace ire::client::objects
{
    ObjectMenager::ObjectMenager()
    {
    }

    void ObjectMenager::appendBuildingsToVector(std::unique_ptr<Building> building)
    {
        m_collectionOfBuildings.push_back(std::move(building));
    }
    std::vector<core::world::TileOverlay> ObjectMenager::getOverlayVector(sf::Vector2i mousePosition)
    {
        std::vector<core::world::TileOverlay> tileOverlays;
        for (auto& building : m_collectionOfBuildings)
        {
            switch (building->getState())
            {
            case Building::States::Planned:
                building->updatePlannedOverlay(mousePosition);
                tileOverlays.push_back(building->getPlannedOverlay());
                break;
            case Building::States::Ordered:
                tileOverlays.push_back(building->getOrderedOverlay());
            default:
                break;
            }
        }
        return tileOverlays;
    }

    const bool ObjectMenager::isCollectionOfBuildingsEmpty() const
    {
        return m_collectionOfBuildings.empty();
    }

    void ObjectMenager::setPlanning(bool isPlanning)
    {
        if (m_isPlanning != isPlanning)
        {
            m_isPlanning = isPlanning;
        }
    }

    const bool ObjectMenager::isPlanning() const
    {
        return m_isPlanning;
    }
}