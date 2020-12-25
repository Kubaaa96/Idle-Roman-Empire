#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

namespace ire::core::world
{

    // Base class for a surface. Will get virtual methods as we narrow down on the needed interface.
    struct Surface
    {
        virtual void draw(sf::RenderTarget& target) = 0;
    };

}
