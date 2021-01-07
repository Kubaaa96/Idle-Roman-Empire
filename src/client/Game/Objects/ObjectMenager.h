#ifndef IRE_OBJECT_MENAGER_H
#define IRE_OBJECT_MENAGER_H

#include <vector>
#include "Building.h"

namespace ire::client::objects
{
    struct ObjectMenager
    {
        enum struct States
        {
            Null,
            Planning,
            Building
        };

        [[nodiscard]] const States getState() const;

    protected:
        States m_state = States::Null;

        std::vector<Building> m_collectionOfBuildings;
    };
}

#endif //!IRE_OBJECT_MENAGER_H