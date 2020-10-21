#include <catch2/catch.hpp>

#include "core/util/UpdatablePriorityQueue.h"

#include <functional>

TEST_CASE("General invariants of the priority queue", "[updatable_priority_queue]")
{
    using namespace ire::core::util;

    UpdatablePriorityQueue<int, std::greater<>> v;

    REQUIRE(v.isEmpty());

    auto id = v.emplace(123);

    REQUIRE(!v.isEmpty());

    v.remove(id);

    REQUIRE(v.isEmpty());

    v.emplace(0);

    REQUIRE(v.top() == 0);

    id = v.emplace(-1);

    REQUIRE(v.top() == -1);

    v.remove(id);

    REQUIRE(v.top() == 0);

    v.pop();

    REQUIRE(v.isEmpty());

    for (int i = 0; i < 100; ++i)
    {
        v.remove(v.emplace(i));
    }

    REQUIRE(v.isEmpty());

    for (int i = 0; i < 100; ++i)
    {
        v.emplace(99 - i);
    }

    for (int i = 0; i < 100; ++i)
    {
        REQUIRE(!v.isEmpty());
        REQUIRE(v.top() == i);
        v.pop();
    }

    REQUIRE(v.isEmpty());
}