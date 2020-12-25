#pragma once

#include "core/world/Surface.h"

namespace ire::core::world
{

    struct TiledTopDownSurface : Surface
    {
        TiledTopDownSurface(int width, int height);

        void draw(sf::RenderTarget& target) override;

    private:
        int m_width;
        int m_height;
    };

}
