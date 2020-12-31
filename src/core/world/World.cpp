#include "World.h"

namespace ire::core::world
{
    World::World(std::unique_ptr<Surface> mainSurface)
    {
        m_surfaces.emplace_back(std::move(mainSurface));
    }

    [[nodiscard]] const Surface& World::getMainSurface() const
    {
        return *m_surfaces.front();
    }

    [[nodiscard]] Surface& World::getMainSurface()
    {
        return *m_surfaces.front();
    }
}