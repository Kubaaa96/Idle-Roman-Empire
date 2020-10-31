#include <catch2/catch.hpp>

template<typename T>
bool areAlmostEqual(T sfvector, T sfvector2) 
{ 
    return sfvector.x == Approx(sfvector2.x) && sfvector.y == Approx(sfvector2.y);
}