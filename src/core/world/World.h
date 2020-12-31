#pragma once

#include "Surface.h"

#include <memory>
#include <vector>

namespace ire::core::world
{
    
    struct World
    {
        World(std::unique_ptr<Surface> mainSurface);

        [[nodiscard]] const Surface& getMainSurface() const;
        [[nodiscard]] Surface& getMainSurface();

    private:
        std::vector<std::unique_ptr<Surface>> m_surfaces;
    };

}
