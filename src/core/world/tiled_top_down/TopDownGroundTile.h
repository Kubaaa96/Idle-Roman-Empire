#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ire::core::world
{

    struct TopDownGroundTile
    {
        explicit TopDownGroundTile(sf::Color tint = sf::Color::White) :
            m_tint(tint)
        {
        }

        [[nodiscard]] sf::Color getTint() const
        {
            return m_tint;
        }

    private:
        sf::Color m_tint;
    };

}
