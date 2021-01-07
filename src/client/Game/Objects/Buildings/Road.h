#ifndef IRE_ROAD_H
#define IRE_ROAD_H

#include "client/Game/Objects/Building.h"

namespace ire::client::objects
{
    struct Road : Building
    {
        void initializeOverlay() override;

    protected:
        void setupPlannedOverlay();
        void setupOrderedOverlay();
        void setupInProductionOverlay();
        void setupIdleOverlay();
    };
}


#endif //!IRE_ROAD_H