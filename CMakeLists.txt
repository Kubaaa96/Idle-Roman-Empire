cmake_minimum_required(VERSION 3.1)

project(IdleRomanEmpire)

add_custom_target(IdleRomanEmpire)

### Setup variables

set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo MinSizeRel)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/")

set(CMAKE_MAP_IMPORTED_CONFIG_MINSIZEREL MinSizeRel RelWithDebInfo Release Debug)
set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO RelWithDebInfo Release MinSizeRel Debug)
set(CMAKE_MAP_IMPORTED_CONFIG_RELEASE Release RelWithDebInfo MinSizeRel Debug)

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build Idle Roman Empire Tests ?")
endif()

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

### Setup library dependencies

if (NOT DEFINED SFML_STATIC_LIBRARIES)
    set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Choose whether SFML is linked statically or not.")
endif()

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

find_package(Threads REQUIRED)

add_subdirectory(libs/catch)

add_subdirectory(libs/asio)

### Gather IRE components

add_subdirectory(src)

if (BUILD_TESTS)
    include_directories(${CMAKE_PREFIX_PATH}/src)
    add_subdirectory(tests)
    add_dependencies(IdleRomanEmpire IRETests)
endif()

add_dependencies(IdleRomanEmpire IREComponents)
