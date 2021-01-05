#pragma once

#include <vector>
#include <optional>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "core/util/FourWay.h"

#include "core/gfx/TextureAtlas.h"

namespace ire::core::world
{

    struct TileOverlayBorder
    {
        util::FourWay<bool> visible;
        sf::Color color;
        float thickness;
    };

    struct TileOverlaySprite
    {
        gfx::TextureView sprite;
        sf::Vector2f size;
    };

    struct TileOverlay
    {
        sf::Vector2i position;
        std::optional<TileOverlayBorder> border;
        std::optional<TileOverlaySprite> sprite;
    };

}