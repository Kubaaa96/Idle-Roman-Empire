cmake_minimum_required(VERSION 3.1)

project(IdleRomanEmpire)

add_subdirectory(libs/catch)
add_subdirectory(libs/asio)
# add_subdirectory(libs/fmt)

# For some reason the include_directories within catch is not enough.
# This is a temporary workaround.
include_directories(libs/catch/include)
include_directories(src)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

if (NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
  message("Setting CMAKE_BUILD_TYPE to ${CMAKE_BUILD_TYPE}")
endif()

if (WIN32)
  if (DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
    message("Setting VCPKG_TARGET_TRIPLET to ${VCPKG_TARGET_TRIPLET}")
  endif()

  if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message("Setting CMAKE_TOOLCHAIN_FILE to ${CMAKE_TOOLCHAIN_FILE}")
  elseif (DEFINED ENV{VCPKG_INSTALLATION_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    message("Setting CMAKE_TOOLCHAIN_FILE to ${CMAKE_TOOLCHAIN_FILE}")
  endif()

  # We have to help in finding SFML because setting CMAKE_TOOLCHAIN_FILE for VCPKG is not enough apparently...
  if (NOT DEFINED SFML_DIR AND DEFINED ENV{VCPKG_ROOT})
    set(SFML_DIR "$ENV{VCPKG_ROOT}/packages/sfml_${VCPKG_TARGET_TRIPLET}/share/sfml")
    message("Setting SFML_DIR to ${SFML_DIR}")
  elseif (NOT DEFINED SFML_DIR AND DEFINED ENV{VCPKG_INSTALLATION_ROOT})
    set(SFML_DIR "$ENV{VCPKG_INSTALLATION_ROOT}/packages/sfml_${VCPKG_TARGET_TRIPLET}/share/sfml")
    message("Setting SFML_DIR to ${SFML_DIR}")
  endif()
endif()

if (NOT DEFINED SFML_STATIC_LIBRARIES)
    set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Choose whether SFML is linked statically or not.")
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resource/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests/resource/)

set(IDLEROMANEMPIRE_STATIC_STD_LIBS FALSE CACHE BOOL "Use statically linked standard/runtime libraries? This option must match the one used for SFML.")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED CONFIG PATHS ${SFML_DIR})

if(NOT SFML_FOUND)
	message("\n-> SFML libraries were not found. Set SFML_DIR to SFML's CMake Config path (generally located in \"lib/cmake/SFML\").")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

add_subdirectory(src/core)

file(GLOB_RECURSE CLIENT_HEADERS "src/client/*.h")
file(GLOB_RECURSE CLIENT_SOURCES "src/client/*.cpp")

add_executable(IdleRomanEmpire ${CLIENT_HEADERS} ${CLIENT_SOURCES})

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build Idle Roman Empire Tests ?")
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

find_package(Threads REQUIRED)
target_link_libraries(IdleRomanEmpire Threads::Threads)

target_link_libraries(IdleRomanEmpire IRECore)
target_link_libraries(IdleRomanEmpire sfml-graphics sfml-audio sfml-window sfml-system)
target_link_libraries(IdleRomanEmpire asio)

install(TARGETS IdleRomanEmpire RUNTIME DESTINATION .)

