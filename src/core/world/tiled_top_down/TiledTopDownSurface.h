#pragma once

#include "TopDownGroundTile.h"
#include "TopDownGridPoint.h"

#include "core/resource/Resource.h"

#include "core/gfx/TextureAtlas.h"

#include "core/util/Array2.h"

#include "core/world/Surface.h"

#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

namespace ire::core::world
{

    struct TiledTopDownSurface : Surface
    {
        TiledTopDownSurface(int width, int height);

        void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

        [[nodiscard]] sf::Vector3f getGridPointNormal(int x, int y) const;
        [[nodiscard]] sf::Vector3f getGroundNormal(float x, float y) const;

    private:
        struct GroundChunkCache
        {
            GroundChunkCache()
            {
                vbo.create(1);
            }

            sf::VertexBuffer vbo = sf::VertexBuffer(sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static);
            unsigned vertexCount = 0;
            bool isDirty = true;
        };

        static constexpr int chunkSize = 16;

        int m_width;
        int m_height;

        util::Array2<TopDownGroundTile> m_tiles;
        util::Array2<TopDownGridPoint> m_gridPoints;

        ResourcePtr<gfx::TextureAtlas> m_textureAtlas;
        gfx::TextureView m_tileSprite;
        float m_elevationSqueeze;

        util::Array2<GroundChunkCache> m_groundChunkCache;

        void appendGroundTileGeometry(std::vector<sf::Vertex>& va, int x, int y);
        void generateRandomWorld();

        void drawGround(sf::RenderTarget& target, sf::RenderStates& states);

        GroundChunkCache& updateChunkCacheIfRequired(int cx, int cy);
    };

}
