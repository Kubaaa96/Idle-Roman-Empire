#pragma once

#include <SFML/System/Vector3.hpp>

#include <cmath>

namespace ire::core::util
{

    [[nodiscard]] inline float dot(const sf::Vector3f& a, const sf::Vector3f& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    [[nodiscard]] inline sf::Vector3f cross(const sf::Vector3f& a, const sf::Vector3f& b)
    {
        return sf::Vector3f(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    [[nodiscard]] inline float length(const sf::Vector3f& a)
    {
        return std::sqrt(dot(a, a));
    }

    [[nodiscard]] inline sf::Vector3f normalized(const sf::Vector3f& a)
    {
        return a / length(a);
    }

    inline void normalize(sf::Vector3f& a)
    {
        a /= length(a);
    }

}