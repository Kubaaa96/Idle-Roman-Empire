project(IdleRomanEmpireTests)

include(CTest)
enable_testing()

add_executable(IdleRomanEmpireTests 
    # Headers
        
    # Sources
    src/tests.cpp)

target_link_libraries(IdleRomanEmpireTests catch)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(IdleRomanEmpireTests)
