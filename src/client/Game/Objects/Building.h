#ifndef IRE_BUILDING_H
#define IRE_BUILDING_H

#include "Object.h"
#include "core/world/tiled_top_down/TileOverlay.h"

namespace ire::client::objects
{
    struct Building : Object
    {
        enum struct States
        {
            Null,
            Planned,
            Ordered,
            InProduction,
            Idle,
            Working,
            Full,
            Demaged
        };

        Building();

        virtual void initializeOverlay() {};

        void draw(sf::RenderTarget& target) override;

        [[nodiscard]] const States getState() const;

        [[nodiscard]] core::world::TileOverlay updateOverlay();

    protected:
        // Needed Workers
        // Curent Workers
        States m_state = States::Null;

        virtual void setupPlannedOverlay() {};
        core::world::TileOverlay m_plannedOverlay;

        virtual void setupOrderedOverlay() {};
        core::world::TileOverlay m_orderedOverlay;

        virtual void setupInProductionOverlay() {};
        core::world::TileOverlay m_inProductionOverlay;

        virtual void setupIdleOverlay() {};
        core::world::TileOverlay m_idleOverlay;
        // Size
        // Entrances

    };
}

#endif //!IRE_BUILDING_H