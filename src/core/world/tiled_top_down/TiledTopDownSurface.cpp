#include "TiledTopDownSurface.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>

namespace ire::core::world
{

    TiledTopDownSurface::TiledTopDownSurface(int width, int height) :
        m_width(width),
        m_height(height)
    {
    }

    void TiledTopDownSurface::draw(sf::RenderTarget& target)
    {
        constexpr float cameraAngleDeg = 60.0f;

        const float pi = 3.14159265358979323846f;
        const float degToRad = (2.0f * pi / 360.0f);
        const float cameraAngleRad = cameraAngleDeg * degToRad;
        const float verticalSqueeze = std::sin(cameraAngleRad);

        const auto oldView = target.getView();
        const float oldViewportWidth = target.getViewport(oldView).width;
        const float oldViewportHeight = target.getViewport(oldView).height;
        const float aspectRatio = oldViewportWidth / oldViewportHeight;

        sf::View surfaceView;
        surfaceView.setCenter(10.0f, 10.0f);
        surfaceView.setSize(10.0f * aspectRatio, 10.0f / verticalSqueeze);
        surfaceView.setViewport(oldView.getViewport());
        surfaceView.zoom(1.0f);
        target.setView(surfaceView);

        sf::RectangleShape tileMockup;
        tileMockup.setPosition(sf::Vector2f(10.0f, 10.0f));
        tileMockup.setSize(sf::Vector2f(1.0f, 1.0f));
        tileMockup.setFillColor(sf::Color::Green);
        target.draw(tileMockup);

        target.setView(oldView);
    }

}