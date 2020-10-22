project(IRECore)

file(GLOB_RECURSE CORE_HEADERS "*.h")
file(GLOB_RECURSE CORE_SOURCES "*.cpp")

add_library(IRECore ${CORE_HEADERS} ${CORE_SOURCES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(IRECore sfml-graphics sfml-audio sfml-window sfml-system)
