project(IREClient)

add_executable(IREClient
    # Headers

    # Sources
    main.cpp
)
target_link_libraries(IREClient sfml-graphics sfml-audio sfml-window sfml-system)