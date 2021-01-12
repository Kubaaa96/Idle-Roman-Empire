#ifndef IRE_OBJECT_MANAGER_H
#define IRE_OBJECT_MANAGER_H

#include <vector>
#include "Building.h"

namespace ire::core::world::objects
{
    struct ObjectManager
    {

        ObjectManager();

        void appendBuildingsToVector(std::unique_ptr<Building> building);

        std::vector<core::world::TileOverlay> getOverlayVector(sf::Vector2i mousePosition);

        const bool isEmpty() const;

        void setPlanning(bool isPlanning);
        const bool isPlanning() const;

        void setSelectedBuilding(Building* selectedBuilding);
        Building* getSelectedBuilding();

        void setCanBePlaced(bool canBePlaced);
        const bool canBePlaced() const;

    protected:
        bool m_isPlanning = false;
        bool m_canBePlaced = true;

        Building* m_selectedBuilding = nullptr;

        std::vector<std::unique_ptr<Building>> m_buildings;
    };
}

#endif //!IRE_OBJECT_MANAGER_H