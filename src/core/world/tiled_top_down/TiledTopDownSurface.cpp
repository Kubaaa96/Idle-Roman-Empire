#include "TiledTopDownSurface.h"

#include "core/util/Math.h"

#include "core/resource/ResourceManager.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>
#include <cstdlib>

#include <iostream>

namespace ire::core::world
{

    TiledTopDownSurface::TiledTopDownSurface(int width, int height, 
            std::unique_ptr<core::world::objects::ObjectManager> objectMenager) :
        m_width(width),
        m_height(height),
        m_tiles(width, height),
        m_gridPoints(width + 1, height + 1),
        m_groundChunkCache((width + (chunkSize - 1)) / chunkSize, (height + (chunkSize - 1)) / chunkSize),
        m_objectManager(std::move(objectMenager))
    {
        m_textureAtlas = ResourceManager::instance().get<gfx::TextureAtlas>("resource/gfx/tiles");
        m_tileSprite = m_textureAtlas->getTextureView(ResourcePath("grass.png"));
        
        m_cameraCenter = sf::Vector2f(m_width / 2.0f, m_height / 2.0f);
        m_zoom = 32.0f;

        m_lightDirection = sf::Vector3f(0.3, -0.6, -0.845);

        m_gamma = 2.2f;
        m_ambientLight = sf::Vector3f(0.05f, 0.05f, 0.05f);
        m_sunLight = sf::Vector3f(1.0f, 1.0f, 1.0f);

        generateRandomWorld();
    }

    [[nodiscard]] sf::FloatRect TiledTopDownSurface::getCameraBounds(sf::RenderTarget& target) const
    {
        const auto oldView = target.getView();
        const float oldViewportWidth = target.getViewport(oldView).width;
        const float oldViewportHeight = target.getViewport(oldView).height;
        const float aspectRatio = oldViewportWidth / oldViewportHeight;

        const float viewHeight = oldViewportHeight / m_zoom;
        const float viewWidth = viewHeight * aspectRatio * verticalSqueeze;

        return sf::FloatRect(m_cameraCenter.x - viewWidth / 2.0, m_cameraCenter.y - viewHeight / 2.0, viewWidth, viewHeight);
    }

    [[nodiscard]] sf::View TiledTopDownSurface::getCameraView(sf::RenderTarget& target) const
    {
        auto bounds = getCameraBounds(target);

        sf::View surfaceView;
        surfaceView.setCenter(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        surfaceView.setSize(bounds.width, bounds.height);
        surfaceView.setViewport(target.getView().getViewport());
        surfaceView.zoom(1.0f);

        return surfaceView;
    }

    void TiledTopDownSurface::changeZoom(float multiplier) 
    {
        m_zoom *= multiplier;
    }

    void TiledTopDownSurface::moveCamera(sf::Vector2f diff)
    {
        m_cameraCenter += diff;
    }

    void TiledTopDownSurface::setTileOverlays(std::vector<TileOverlay>&& overlays)
    {
        m_tileOverlays = std::move(overlays);
    }

    void TiledTopDownSurface::resetTileOverlays()
    {
        m_tileOverlays.clear();
    }

    [[nodiscard]] sf::Vector2f TiledTopDownSurface::mapClientToWorldPosition(sf::RenderTarget& target, sf::Vector2f clientPos) const
    {
        // TODO: do this more efficiently
        // TODO: do a proper raycast
        auto cameraView = getCameraView(target);
        return target.mapPixelToCoords(sf::Vector2i(clientPos), cameraView);
    }

    [[nodiscard]] std::optional<sf::Vector2i> TiledTopDownSurface::mapClientToTilePosition(sf::RenderTarget& target) const
    {
        auto worldPos = sf::Vector2i(mapClientToWorldPosition(target, *m_mousePos));
        if (
            worldPos.x < 0
            || worldPos.y < 0
            || worldPos.x >= m_width
            || worldPos.y >= m_height)
        {
            return std::nullopt;
        }

        return worldPos;
    }

    [[nodiscard]] std::vector<TileOverlay> TiledTopDownSurface::getSpriteOverlays() const
    {
        return m_tileOverlays;
    }

    [[nodiscard]] float TiledTopDownSurface::getZoom() const
    {
        return m_zoom;
    }

    void TiledTopDownSurface::setMousePos(std::optional<sf::Vector2f> mousePos)
    {
        if (m_mousePos != mousePos)
        {
            m_mousePos = mousePos;
        }
    }

    objects::ObjectManager* TiledTopDownSurface::getObjectMenager()
    {
        return m_objectManager.get();
    }

    void TiledTopDownSurface::draw(sf::RenderTarget& target, sf::RenderStates& states)
    {
        constexpr float cameraAngleDeg = 60.0f;

        auto oldView = target.getView();
        auto surfaceView = getCameraView(target);
        target.setView(surfaceView);
        
        if (m_mousePos.has_value())
        {
            auto pointedTilePos = mapClientToTilePosition(target);
            if (pointedTilePos.has_value())
            {
                if (!m_objectManager->isEmpty())
                {
                    setTileOverlays(m_objectManager->getOverlayVector(*pointedTilePos));
                }
            }
            else
            {
                resetTileOverlays();
            }
        }
        
        drawGround(target, states);
        drawTileOverlays(target, states);

        target.setView(oldView);
    }

    void TiledTopDownSurface::generateRandomWorld()
    {
        for (int x = 0; x < m_width; ++x)
        {
            for (int y = 0; y < m_height; ++y)
            {
                m_tiles(x, y) = TopDownGroundTile(sf::Color(rand(), rand(), rand()));
            }
        }

        util::Array2<float> elevation(m_width + 3, m_height + 3);
        for (int x = 0; x < m_width + 3; ++x)
        {
            for (int y = 0; y < m_height + 3; ++y)
            {
                elevation(x, y) = rand() % 100 / 10.0f;
            }
        }

        for (int x = 0; x < m_width + 1; ++x)
        {
            for (int y = 0; y < m_height + 1; ++y)
            {
                float sum = 0.0f;
                for (int xx = 0; xx < 2; ++xx)
                {
                    for (int yy = 0; yy < 2; ++yy)
                    {
                        sum += elevation(x + xx, y + yy);
                    }
                }
                m_gridPoints(x, y) = TopDownGridPoint(sum / 9.0f);
            }
        }
    }

    void TiledTopDownSurface::appendGroundTileGeometry(std::vector<sf::Vertex>& va, int x, int y)
    {
        const auto groundToSun = util::normalized(-m_lightDirection);

        auto appendTriangle = [&](
            sf::Vector3f v0, sf::Vector3f v1, sf::Vector3f v2,
            sf::Vector2f t0, sf::Vector2f t1, sf::Vector2f t2
            )
        {
            auto applyGamma = [this](const sf::Vector3f& c) {
                return sf::Color(
                    std::clamp((int)(std::pow(c.x, 1.0f / m_gamma) * 255.0f), 0, 255),
                    std::clamp((int)(std::pow(c.y, 1.0f / m_gamma) * 255.0f), 0, 255),
                    std::clamp((int)(std::pow(c.z, 1.0f / m_gamma) * 255.0f), 0, 255)
                );
            };

            auto getColor = [&](sf::Vector3f normal)
            {
                const float sunLightIntensity = std::max(0.0f, util::dot(normal, groundToSun));
                const auto colorLin = m_sunLight * sunLightIntensity + m_ambientLight;
                const auto color = applyGamma(colorLin);
                return color;
            };

            auto n0 = getGroundNormal(v0.x, v0.y);
            auto n1 = getGroundNormal(v1.x, v1.y);
            auto n2 = getGroundNormal(v2.x, v2.y);
            auto c0 = getColor(n0);
            auto c1 = getColor(n1);
            auto c2 = getColor(n2);
            va.emplace_back(sf::Vector2f(v0.x, v0.y - v0.z * elevationSqueeze), c0, t0);
            va.emplace_back(sf::Vector2f(v1.x, v1.y - v1.z * elevationSqueeze), c1, t1);
            va.emplace_back(sf::Vector2f(v2.x, v2.y - v2.z * elevationSqueeze), c2, t2);
        };

        const auto topLeftElevation = m_gridPoints(x, y).getElevation();
        const auto topRightElevation = m_gridPoints(x + 1, y).getElevation();
        const auto bottomRightElevation = m_gridPoints(x + 1, y + 1).getElevation();
        const auto bottomLeftElevation = m_gridPoints(x, y + 1).getElevation();
        const auto midElevation = 
            (topLeftElevation
            + topRightElevation
            + bottomRightElevation
            + bottomLeftElevation) * 0.25f;

        const auto topLeft = sf::Vector3f(x, y, topLeftElevation);
        const auto topRight = sf::Vector3f(x + 1, y, topRightElevation);
        const auto bottomRight = sf::Vector3f(x + 1, y + 1, bottomRightElevation);
        const auto bottomLeft = sf::Vector3f(x, y + 1, bottomLeftElevation);
        const auto mid = sf::Vector3f(x + 0.5f, y + 0.5f, midElevation);

        const auto& texture = m_tileSprite.getTexture();
        const auto& texBounds = m_tileSprite.getBounds();
        const auto topLeftTex = sf::Vector2f(texBounds.left, texBounds.top);
        const auto topRightTex = sf::Vector2f(texBounds.left + texBounds.width, texBounds.top);
        const auto bottomRightTex = sf::Vector2f(texBounds.left + texBounds.width, texBounds.top + texBounds.height);
        const auto bottomLeftTex = sf::Vector2f(texBounds.left, texBounds.top + texBounds.height);
        const auto midTex = sf::Vector2f(texBounds.left + texBounds.width * 0.5f, texBounds.top + texBounds.height * 0.5f);

        appendTriangle(mid, bottomLeft, topLeft, midTex, bottomLeftTex, topLeftTex);
        appendTriangle(mid, bottomRight, bottomLeft, midTex, bottomRightTex, bottomLeftTex);
        appendTriangle(mid, topRight, bottomRight, midTex, topRightTex, bottomRightTex);
        appendTriangle(mid, topLeft, topRight, midTex, topLeftTex, topRightTex);
    }

    void TiledTopDownSurface::drawGround(sf::RenderTarget& target, sf::RenderStates& states)
    {
        const int wc = (m_width + (chunkSize - 1)) / chunkSize;
        const int hc = (m_height + (chunkSize - 1)) / chunkSize;

        auto cameraBounds = getCameraBounds(target);

        states.texture = &m_tileSprite.getTexture();
        for (int cy = 0; cy < hc; ++cy)
        {
            for (int cx = 0; cx < wc; ++cx)
            {
                auto& chunk = updateChunkCacheIfRequired(cx, cy);
                if (chunk.bounds.intersects(cameraBounds))
                {
                    target.draw(chunk.vbo, 0, chunk.vertexCount, states);
                }
            }
        }
    }

    void TiledTopDownSurface::drawTileOverlays(sf::RenderTarget& target, sf::RenderStates& states)
    {
        for (auto& overlay : m_tileOverlays)
        {
            drawTileOverlay(target, states, overlay);
        }
    }

    void TiledTopDownSurface::drawTileOverlay(sf::RenderTarget& target, sf::RenderStates& states, const TileOverlay& overlay)
    {
        if (overlay.border.has_value())
        {
            drawTileOverlayBorder(target, states, *(overlay.border), overlay.position);
        }

        if (overlay.sprite.has_value())
        {
            drawTileOverlaySprite(target, states, *(overlay.sprite), overlay.position);
        }
    }

    void TiledTopDownSurface::drawTileOverlayBorder(sf::RenderTarget& target, sf::RenderStates& states, const TileOverlayBorder& overlay, const sf::Vector2i& position)
    {
        sf::VertexArray va(sf::Triangles);
        
        const auto x = position.x;
        const auto y = position.y;

        const auto topLeftElevation = m_gridPoints(x, y).getElevation();
        const auto topRightElevation = m_gridPoints(x + 1, y).getElevation();
        const auto bottomRightElevation = m_gridPoints(x + 1, y + 1).getElevation();
        const auto bottomLeftElevation = m_gridPoints(x, y + 1).getElevation();
        const auto midElevation =
            (topLeftElevation
            + topRightElevation
            + bottomRightElevation
            + bottomLeftElevation) * 0.25f;

        const auto topLeft = sf::Vector2f(x, y - topLeftElevation * elevationSqueeze);
        const auto topRight = sf::Vector2f(x + 1, y - topRightElevation * elevationSqueeze);
        const auto bottomRight = sf::Vector2f(x + 1, y + 1 - bottomRightElevation * elevationSqueeze);
        const auto bottomLeft = sf::Vector2f(x, y + 1 - bottomLeftElevation * elevationSqueeze);
        const auto mid = sf::Vector2f(x + 0.5f, y + 0.5f - midElevation * elevationSqueeze);

        const auto color = overlay.color;
        const auto thickness = overlay.thickness;
        const auto halfThickness = thickness * 0.5f;

        const auto outwardTopLeft = (topLeft - mid) * halfThickness;
        const auto outwardTopRight = (topRight - mid) * halfThickness;
        const auto outwardBottomRight = (bottomRight - mid) * halfThickness;
        const auto outwardBottomLeft = (bottomLeft - mid) * halfThickness;

        const auto vTopLeftOuter = sf::Vertex(topLeft + outwardTopLeft, color);
        const auto vTopLeftInner = sf::Vertex(topLeft - outwardTopLeft, color);
        const auto vTopRightOuter = sf::Vertex(topRight + outwardTopRight, color);
        const auto vTopRightInner = sf::Vertex(topRight - outwardTopRight, color);
        const auto vBottomRightOuter = sf::Vertex(bottomRight + outwardBottomRight, color);
        const auto vBottomRightInner = sf::Vertex(bottomRight - outwardBottomRight, color);
        const auto vBottomLeftOuter = sf::Vertex(bottomLeft + outwardBottomLeft, color);
        const auto vBottomLeftInner = sf::Vertex(bottomLeft - outwardBottomLeft, color);

        if (overlay.visible.top)
        {
            va.append(vTopLeftOuter);
            va.append(vTopLeftInner);
            va.append(vTopRightOuter);

            va.append(vTopLeftInner);
            va.append(vTopRightOuter);
            va.append(vTopRightInner);
        }

        if (overlay.visible.right && bottomRight.y > topRight.y)
        {
            va.append(vTopRightOuter);
            va.append(vTopRightInner);
            va.append(vBottomRightOuter);

            va.append(vTopRightInner);
            va.append(vBottomRightOuter);
            va.append(vBottomRightInner);
        }

        if (overlay.visible.bottom)
        {
            va.append(vBottomRightOuter);
            va.append(vBottomRightInner);
            va.append(vBottomLeftOuter);

            va.append(vBottomRightInner);
            va.append(vBottomLeftOuter);
            va.append(vBottomLeftInner);
        }

        if (overlay.visible.left && bottomLeft.y > topLeft.y)
        {
            va.append(vBottomLeftOuter);
            va.append(vBottomLeftInner);
            va.append(vTopLeftOuter);

            va.append(vBottomLeftInner);
            va.append(vTopLeftOuter);
            va.append(vTopLeftInner);
        }

        target.draw(va);
    }

    void TiledTopDownSurface::drawTileOverlaySprite(sf::RenderTarget& target, sf::RenderStates& states, const TileOverlaySprite& overlay, const sf::Vector2i& position)
    {
        const auto x = position.x;
        const auto y = position.y;

        const auto topLeftElevation = m_gridPoints(x, y).getElevation();
        const auto topRightElevation = m_gridPoints(x + 1, y).getElevation();
        const auto bottomRightElevation = m_gridPoints(x + 1, y + 1).getElevation();
        const auto bottomLeftElevation = m_gridPoints(x, y + 1).getElevation();
        const auto midElevation =
            (topLeftElevation
            + topRightElevation
            + bottomRightElevation
            + bottomLeftElevation) * 0.25f;

        const auto mid = sf::Vector2f(x + 0.5f, y + 0.5f - midElevation * elevationSqueeze);

        const auto halfSize = sf::Vector2f(overlay.size.x * 0.5f, overlay.size.y * 0.5f * verticalSqueeze);

        const auto& texBounds = overlay.sprite.getBounds();
        const auto& texture = overlay.sprite.getTexture();

        const auto topLeftTex = sf::Vector2f(texBounds.left, texBounds.top);
        const auto topRightTex = sf::Vector2f(texBounds.left + texBounds.width, texBounds.top);
        const auto bottomRightTex = sf::Vector2f(texBounds.left + texBounds.width, texBounds.top + texBounds.height);
        const auto bottomLeftTex = sf::Vector2f(texBounds.left, texBounds.top + texBounds.height);

        sf::RectangleShape sprite;
        sprite.setPosition(mid - halfSize);
        sprite.setSize(halfSize * 2.0f);
        sprite.setFillColor(sf::Color::Cyan);
        sprite.setTexture(&texture);
        sprite.setTextureRect(sf::IntRect(texBounds));

        target.draw(sprite);
    }

    [[nodiscard]] sf::Vector3f TiledTopDownSurface::getGridPointNormal(int x, int y) const
    {
        // Probe elevations at 3 nearby points in each axis.
        const sf::Vector3f x0(std::max(0, x - 1), y, m_gridPoints(std::max(0, x - 1), y).getElevation());
        const sf::Vector3f x1(x, y, m_gridPoints(x, y).getElevation());
        const sf::Vector3f x2(std::min(m_width, x + 1), y, m_gridPoints(std::min(m_width, x + 1), y).getElevation());
        const sf::Vector3f y0(x, std::max(0, y - 1), m_gridPoints(x, std::max(0, y - 1)).getElevation());
        const sf::Vector3f y1(x, y, m_gridPoints(x, y).getElevation());
        const sf::Vector3f y2(x, std::min(m_height, y + 1), m_gridPoints(x, std::min(m_height, y + 1)).getElevation());

        // Compute gradients. For points A, B, C lying on the same axis
        // we use a gradient between the midpoints of AB and BC.
        const sf::Vector3f a = (x1 + x0) * 0.5f - (x2 + x1) * 0.5f;
        const sf::Vector3f b = (y1 + y0) * 0.5f - (y2 + y1) * 0.5f;

        // Get normal of the triangle formed by the gradients.
        const sf::Vector3f normal = util::normalized(util::cross(a, b));

        return normal;
    }

    [[nodiscard]] sf::Vector3f TiledTopDownSurface::getGroundNormal(float x, float y) const
    {
        // Get neighbouring grid coords.
        const int x0 = x;
        const int x1 = x0 + 1;
        const int y0 = y;
        const int y1 = y0 + 1;

        // Get interpolation factors.
        const float dx = x - x0;
        const float dy = y - y0;

        // Get grid point normals.
        const sf::Vector3f n00 = getGridPointNormal(x0, y0);
        const sf::Vector3f n10 = getGridPointNormal(x1, y0);
        const sf::Vector3f n11 = getGridPointNormal(x1, y1);
        const sf::Vector3f n01 = getGridPointNormal(x0, y1);

        // Interpolate bilinearly
        const sf::Vector3f nx0 = n00 * dx + n10 * (1.0f - dx);
        const sf::Vector3f nx1 = n01 * dx + n11 * (1.0f - dx);
        const sf::Vector3f n = nx0 * dy + nx1 * (1.0f - dy);

        return util::normalized(n);
    }

    TiledTopDownSurface::GroundChunkCache& TiledTopDownSurface::updateChunkCacheIfRequired(int cx, int cy)
    {
        auto computeBounds = [](const std::vector<sf::Vertex>& vertices) {
            float xmin = std::numeric_limits<float>::max();
            float ymin = std::numeric_limits<float>::max();
            float xmax = std::numeric_limits<float>::lowest();
            float ymax = std::numeric_limits<float>::lowest();

            for (auto& v : vertices)
            {
                xmin = std::min(xmin, v.position.x);
                xmax = std::max(xmax, v.position.x);

                ymin = std::min(ymin, v.position.y);
                ymax = std::max(ymax, v.position.y);
            }

            return sf::FloatRect(xmin, ymin, xmax - xmin, ymax - ymin);
        };

        auto& chunk = m_groundChunkCache(cx, cy);
        if (!chunk.isDirty)
        {
            return chunk;
        }

        std::vector<sf::Vertex> vertices;
        // Each ground tile now uses 4 triangles.
        vertices.reserve(4 * 3 * chunkSize * chunkSize);
        for (int y = cy * chunkSize; y < cy * chunkSize + chunkSize && y < m_height; ++y)
        {
            for (int x = cx * chunkSize; x < cx * chunkSize + chunkSize && x < m_width; ++x)
            {
                appendGroundTileGeometry(vertices, x, y);
            }
        }

        chunk.isDirty = false;
        chunk.vbo.update(vertices.data(), vertices.size(), 0);
        chunk.vertexCount = vertices.size();
        chunk.bounds = computeBounds(vertices);

        return chunk;
    }

}