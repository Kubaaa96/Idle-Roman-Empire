#pragma once

#include "TopDownGroundTile.h"
#include "TopDownGridPoint.h"

#include "core/util/Array2.h"

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

        util::Array2<TopDownGroundTile> m_tiles;
        util::Array2<TopDownGridPoint> m_gridPoints;

        void generateRandomWorld();

        void drawGround(sf::RenderTarget& target);
    };

}
