project(asio)

add_library(asio INTERFACE)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_include_directories(asio
    INTERFACE
        include/
        )


target_link_libraries(asio INTERFACE Threads::Threads)