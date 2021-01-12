#ifndef IRE_OBJECT_MANAGER_H
#define IRE_OBJECT_MANAGER_H

#include <vector>
#include "Building.h"

namespace ire::client::objects
{
    struct ObjectManager
    {

        ObjectManager();

        void appendBuildingsToVector(std::unique_ptr<Building> building);

        std::vector<core::world::TileOverlay> getOverlayVector(sf::Vector2i mousePosition);

        const bool isEmpty() const;

        void setPlanning(bool isPlanning);
        const bool isPlanning() const;

        Building* m_currentSelectedBuilding = nullptr;

        void setCanBePlaced(bool canBePlaced);
        const bool canBePlaced() const;

    protected:
        bool m_isPlanning = false;
        bool m_canBePlaced = true;
        std::vector<std::unique_ptr<Building>> m_buildings;
    };
}

#endif //!IRE_OBJECT_MANAGER_H