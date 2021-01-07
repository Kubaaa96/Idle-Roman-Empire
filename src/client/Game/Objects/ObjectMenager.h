#ifndef IRE_OBJECT_MENAGER_H
#define IRE_OBJECT_MENAGER_H

#include <vector>
#include "Building.h"

namespace ire::client::objects
{
    struct ObjectMenager
    {

        ObjectMenager();

        void appendBuildingsToVector(std::unique_ptr<Building> building);

        std::vector<core::world::TileOverlay> getOverlayVector(sf::Vector2i mousePosition);

        const bool isCollectionOfBuildingsEmpty() const;

        const bool isPlanning() const;

    protected:
        bool m_isPlanning = false;



        std::vector<std::unique_ptr<Building>> m_collectionOfBuildings;
    };
}

#endif //!IRE_OBJECT_MENAGER_H