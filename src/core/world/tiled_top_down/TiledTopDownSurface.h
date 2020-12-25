#pragma once

#include "TopDownGroundTile.h"
#include "TopDownGridPoint.h"

#include "core/util/Array2.h"

#include "core/world/Surface.h"

#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ire::core::world
{

    struct TiledTopDownSurface : Surface
    {
        TiledTopDownSurface(int width, int height);

        void draw(sf::RenderTarget& target) override;

        [[nodiscard]] sf::Vector3f getGridPointNormal(int x, int y) const;

    private:
        int m_width;
        int m_height;

        util::Array2<TopDownGroundTile> m_tiles;
        util::Array2<TopDownGridPoint> m_gridPoints;

        void drawGroundTile(sf::VertexArray& va, int x, int y);
        void generateRandomWorld();

        void drawGround(sf::RenderTarget& target);
    };

}
