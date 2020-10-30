cmake_minimum_required(VERSION 3.1)

project(IREComponents)

add_custom_target(IREComponents)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(core)

add_subdirectory(client)
add_subdirectory(server)

add_dependencies(IREComponents IRECore IREClient IREServer)
