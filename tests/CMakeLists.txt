project(IRETests)

include(CTest)
enable_testing()

add_executable(IRETests 
    # Headers
        
    # Sources
    src/Catch_Common/tests.cpp)

target_link_libraries(IRETests IRECore)
target_link_libraries(IRETests catch)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(IRETests)

add_dependencies(IRETests IdleRomanEmpire)

target_link_libraries(IRETests sfml-graphics sfml-audio sfml-window sfml-system)
