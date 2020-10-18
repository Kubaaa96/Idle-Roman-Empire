project(catch)

file(GLOB CATCH_HEADERS include/catch.hpp)

add_library(catch INTERFACE)

target_include_directories(catch 
    INTERFACE
        include/
        )