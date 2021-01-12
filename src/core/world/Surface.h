#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "core/world/objects/ObjectManager.h"

namespace ire::core::world
{
    // Base class for a surface. Will get virtual methods as we narrow down on the needed interface.
    struct Surface
    {
        virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) = 0;

        virtual objects::ObjectManager* getObjectMenager() = 0;
    };

}
