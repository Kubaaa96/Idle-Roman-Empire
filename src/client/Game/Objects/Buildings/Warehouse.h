#ifndef IRE_WAREHOUSE_H
#define IRE_WAREHOUSE_H

#include "client/Game/Objects/Building.h"

namespace ire::client::objects
{

    struct Warehouse : Building
    {
        void initializeOverlay() override;

    protected:
        void setupPlannedOverlay();
        void setupOrderedOverlay();
        void setupInProductionOverlay();
        void setupIdleOverlay();
    };

}

#endif //!IRE_WAREHOUSE_H