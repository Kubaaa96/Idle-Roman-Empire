cmake_minimum_required(VERSION 3.1)

project(IdleRomanEmpire)

add_subdirectory(libs/catch)
# add_subdirectory(libs/fmt)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/") 

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Choose whether SFML is linked statically or not.")
set(IDLEROMANEMPIRE_STATIC_STD_LIBS FALSE CACHE BOOL "Use statically linked standard/runtime libraries? This option must match the one used for SFML.")

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

if(NOT SFML_FOUND)
	message("\n-> SFML libraries were not found. Set SFML_DIR to SFML's CMake Config path (generally located in \"lib/cmake/SFML\").")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

add_executable(IdleRomanEmpire 
    # Headers

    # Sources
    src/app/main.cpp)

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build Idle Roman Empire Tests ?")
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

target_link_libraries(IdleRomanEmpire sfml-graphics sfml-audio sfml-window sfml-system)


install(TARGETS IdleRomanEmpire
        RUNTIME DESTINATION .)

