#pragma once

#include "TopDownGroundTile.h"
#include "TopDownGridPoint.h"

#include "TileOverlay.h"

#include "core/resource/Resource.h"

#include "core/gfx/TextureAtlas.h"

#include "core/util/Array2.h"

#include "core/world/Surface.h"

#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>



#include <cmath>
#include <optional>
#include <memory>

namespace ire::core::world
{

    struct TiledTopDownSurface : Surface
    {
        TiledTopDownSurface(int width, int height, std::unique_ptr<core::world::objects::ObjectManager> objectMenager);

        void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

        [[nodiscard]] sf::Vector3f getGridPointNormal(int x, int y) const;
        [[nodiscard]] sf::Vector3f getGroundNormal(float x, float y) const;

        [[nodiscard]] sf::FloatRect getCameraBounds(sf::RenderTarget& target) const;
        [[nodiscard]] sf::View getCameraView(sf::RenderTarget& target) const;

        void changeZoom(float multiplier);
        void moveCamera(sf::Vector2f diff);

        void setTileOverlays(std::vector<TileOverlay>&& overlays);
        void resetTileOverlays();
        [[nodiscard]] std::vector<TileOverlay> getSpriteOverlays() const;

        [[nodiscard]] sf::Vector2f mapClientToWorldPosition(sf::RenderTarget& target, sf::Vector2f clientPos) const;
        [[nodiscard]] std::optional<sf::Vector2i> mapClientToTilePosition(sf::RenderTarget& target) const;

        [[nodiscard]] float getZoom() const;

        void setMousePos(std::optional<sf::Vector2f> mousePos);

        objects::ObjectManager* getObjectMenager() override;

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
            sf::FloatRect bounds;
        };

        static constexpr int chunkSize = 16;
        static constexpr float cameraAngleDeg = 60.0f;
        static inline const float elevationSqueeze = []() {
            const float pi = 3.14159265358979323846f;
            const float degToRad = (2.0f * pi / 360.0f);
            const float cameraAngleRad = cameraAngleDeg * degToRad;
            return std::cos(cameraAngleRad);
        }();
        static inline const float verticalSqueeze = []() {
            const float pi = 3.14159265358979323846f;
            const float degToRad = (2.0f * pi / 360.0f);
            const float cameraAngleRad = cameraAngleDeg * degToRad;
            return std::sin(cameraAngleRad);
        }();

        int m_width;
        int m_height;

        sf::Vector2f m_cameraCenter;
        float m_zoom;

        sf::Vector3f m_lightDirection;
        float m_gamma;
        sf::Vector3f m_ambientLight;
        sf::Vector3f m_sunLight;

        util::Array2<TopDownGroundTile> m_tiles;
        util::Array2<TopDownGridPoint> m_gridPoints;

        ResourcePtr<gfx::TextureAtlas> m_textureAtlas;
        gfx::TextureView m_tileSprite;

        util::Array2<GroundChunkCache> m_groundChunkCache;

        std::optional<sf::Vector2f> m_mousePos;
        std::unique_ptr<objects::ObjectManager> m_objectManager;
        std::vector<TileOverlay> m_tileOverlays;

        void appendGroundTileGeometry(std::vector<sf::Vertex>& va, int x, int y);
        void generateRandomWorld();

        void drawGround(sf::RenderTarget& target, sf::RenderStates& states);

        void drawTileOverlays(sf::RenderTarget& target, sf::RenderStates& states);
        void drawTileOverlay(sf::RenderTarget& target, sf::RenderStates& states, const TileOverlay& overlay);
        void drawTileOverlayBorder(sf::RenderTarget& target, sf::RenderStates& states, const TileOverlayBorder& overlay, const sf::Vector2i& position);
        void drawTileOverlaySprite(sf::RenderTarget& target, sf::RenderStates& states, const TileOverlaySprite& overlay, const sf::Vector2i& position);

        GroundChunkCache& updateChunkCacheIfRequired(int cx, int cy);
    };

}
