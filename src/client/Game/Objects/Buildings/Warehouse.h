#ifndef IRE_WAREHOUSE_H
#define IRE_WAREHOUSE_H

#include "client/Game/Objects/Building.h"

namespace ire::client::objects
{

    struct Warehouse : Building
    {
        void initializeOverlay() override;
        void updatePlannedOverlay(sf::Vector2i mousePosition) override;
        void setupOrderedOverlay(sf::Vector2i clickPosition) override;

    protected:

        void setupInProductionOverlay() override;
        void setupIdleOverlay() override;
    };

}

#endif //!IRE_WAREHOUSE_H