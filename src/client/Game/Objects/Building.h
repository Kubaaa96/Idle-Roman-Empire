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

        void setState(States state);
        [[nodiscard]] const States getState() const;

        virtual void updatePlannedOverlay(sf::Vector2i mousePosition) {};
        const core::world::TileOverlay getPlannedOverlay() const;
        virtual void setupOrderedOverlay(sf::Vector2i clickPosition) {};
        const core::world::TileOverlay getOrderedOverlay() const;
    protected:
        // Needed Workers
        // Curent Workers
        States m_state = States::Null;

        core::world::TileOverlay m_overlay;

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