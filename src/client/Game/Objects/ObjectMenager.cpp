#include "ObjectMenager.h"
#include <algorithm>

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
            std::vector<core::world::TileOverlay> overlays;
            switch (building->getState())
            {
            case Building::States::Planned:
                building->updatePlannedOverlay(mousePosition);
                overlays = building->getPlannedOverlay();
                setCanBePlaced(true);
                for (const auto& overlay : overlays)
                {
                    for (int i = 0; i < tileOverlays.size(); ++i)
                    {
                        if (overlay.position == tileOverlays.at(i).position)
                        {
                            setCanBePlaced(false);
                            tileOverlays.at(i).border->color = sf::Color::Red;
                            tileOverlays.at(i).border->thickness = 0.5f;
                        }
                    }               
                }
                std::move(overlays.begin(), overlays.end(),
                    std::back_inserter(tileOverlays));               
                break;

            case Building::States::Ordered:
                overlays = building->getOrderedOverlay();
                std::move(overlays.begin(), overlays.end(),
                    std::back_inserter(tileOverlays));
                break;
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
    void ObjectMenager::setCanBePlaced(bool canBePlaced)
    {
        m_canBePlaced = canBePlaced;
    }
    const bool ObjectMenager::canBePlaced() const
    {
        return m_canBePlaced;
    }
}