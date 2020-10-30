cmake_minimum_required(VERSION 3.1)

project(IRECore)

file(GLOB_RECURSE CORE_HEADERS "*.h")
file(GLOB_RECURSE CORE_SOURCES "*.cpp")

add_library(IRECore STATIC ${CORE_HEADERS} ${CORE_SOURCES})

set_property(TARGET IRECore PROPERTY CXX_STANDARD 17)
set_property(TARGET IRECore PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(IRECore PRIVATE Threads::Threads)
target_link_libraries(IRECore PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
