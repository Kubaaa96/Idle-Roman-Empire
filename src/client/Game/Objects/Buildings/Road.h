#ifndef IRE_ROAD_H
#define IRE_ROAD_H

#include "client/Game/Objects/Building.h"

namespace ire::client::objects
{
    struct Road : Building
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