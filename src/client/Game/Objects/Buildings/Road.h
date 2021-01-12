#ifndef IRE_ROAD_H
#define IRE_ROAD_H

#include "core/world/objects/Building.h"

namespace ire::client::objects
{
    struct Road : core::world::objects::Building
    {
        Road();

        void initializeOverlay() override;

        void updatePlannedOverlay(sf::Vector2i mousePosition) override;
        void setupOrderedOverlay(sf::Vector2i clickPosition) override;

    protected:

        void setupInProductionOverlay() override;
        void setupIdleOverlay() override;
    };
}


#endif //!IRE_ROAD_H