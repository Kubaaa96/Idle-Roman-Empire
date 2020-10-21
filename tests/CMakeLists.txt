project(IRETests)

include(CTest)
enable_testing()

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(IRETests ${TEST_SOURCES})

target_link_libraries(IRETests IRECore)
target_link_libraries(IRETests catch)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(IRETests)

add_dependencies(IRETests IdleRomanEmpire)

target_link_libraries(IRETests sfml-graphics sfml-audio sfml-window sfml-system)
