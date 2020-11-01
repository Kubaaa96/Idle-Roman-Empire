#include <catch2/catch.hpp>
#include <SFML/Graphics.hpp>

inline bool areAlmostEqual(const sf::Vector2f sfvector, const sf::Vector2f sfvector2)
{ 
    return sfvector.x == Approx(sfvector2.x).epsilon(0.01) && sfvector.y == Approx(sfvector2.y).epsilon(0.01);
}