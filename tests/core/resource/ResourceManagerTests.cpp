#include <catch2/catch.hpp>

#include "MockedResourceLoaders.h"

#include "core/resource/Resource.h"
#include "core/resource/ResourceLoader.h"
#include "core/resource/ResourceManager.h"
#include "core/resource/ResourcePath.h"

#include <string>
#include <filesystem>

TEST_CASE("Test ResourceManager", "[resource]")
{
    using namespace ire::core;

    ResourcePtr<std::string> strResource =
        ResourceManager::instance().get<std::string>("some/path/here.string");
    REQUIRE(*strResource == "TestString here.string");

    ResourcePtr<int> intResource =
        ResourceManager::instance().get<int>("123");
    REQUIRE(*intResource == 123);
}
