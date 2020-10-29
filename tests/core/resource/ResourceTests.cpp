#include <catch2/catch.hpp>

#include "MockedResourceLoaders.h"

#include "core/resource/Resource.h"
#include "core/resource/ResourceLoader.h"
#include "core/resource/ResourcePath.h"

#include <string>
#include <filesystem>
#include <memory>

TEST_CASE("Test EagerResource<T>", "[resource]")
{
    using namespace ire::core;

    detail::EagerResource<std::string> rs("path/to/resource.string");
    REQUIRE(*rs == "TestString resource.string");

    detail::EagerResource<int> ri("123");
    REQUIRE(*ri == 123);
}

TEST_CASE("Test LazyResource<T>", "[resource]")
{
    using namespace ire::core;

    detail::LazyResource<std::string> rs("path/to/resource.string");
    REQUIRE(*rs == "TestString resource.string");

    detail::LazyResource<int> ri("123");
    REQUIRE(*ri == 123);
}
