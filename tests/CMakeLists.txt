project(IRETests)

include(CTest)
enable_testing()

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
file(GLOB_RECURSE TEST_HEADERS "*.h")

add_executable(IRETests ${TEST_SOURCES} ${TEST_HEADERS})

target_link_libraries(IRETests IRECore)
target_link_libraries(IRETests catch)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(IRETests)

include_directories(./)

add_dependencies(IRETests IdleRomanEmpire)

find_package(Threads REQUIRED)
target_link_libraries(IRETests Threads::Threads)
target_link_libraries(IRETests sfml-graphics sfml-audio sfml-window sfml-system)

add_custom_target(IRERunTests COMMAND $<TARGET_FILE:IRETests>)
add_dependencies(IRERunTests IRETests)

install(TARGETS IRETests RUNTIME DESTINATION .)
