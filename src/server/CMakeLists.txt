cmake_minimum_required(VERSION 3.1)

project(IREServer)

file(GLOB_RECURSE SERVER_SOURCES "*.cpp")

add_executable(IREServer ${SERVER_SOURCES})

set_property(TARGET IREServer PROPERTY CXX_STANDARD 17)
set_property(TARGET IREServer PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(IREServer PRIVATE IRECore)
target_link_libraries(IREServer PRIVATE asio)

set(SERVER_INSTALL_DESTINATION "./ire/$<CONFIG>/server/")

if(WIN32)
    target_link_libraries(IREServer PRIVATE wsock32 ws2_32)
endif()

install(TARGETS IREServer RUNTIME DESTINATION ${SERVER_INSTALL_DESTINATION})
