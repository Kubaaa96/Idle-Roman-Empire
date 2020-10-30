cmake_minimum_required(VERSION 3.1)

project(IRETests)

include(CTest)
enable_testing()

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(IRETests ${TEST_SOURCES})

set_property(TARGET IRETests PROPERTY CXX_STANDARD 17)
set_property(TARGET IRETests PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(IRETests Threads::Threads)
target_link_libraries(IRETests IRECore)
target_link_libraries(IRETests catch)
target_link_libraries(IRETests sfml-graphics sfml-audio sfml-window sfml-system)

add_custom_target(IRERunTests
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-graphics> $<TARGET_FILE_DIR:IRETests>/
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-audio> $<TARGET_FILE_DIR:IRETests>/
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-window> $<TARGET_FILE_DIR:IRETests>/
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sfml-system> $<TARGET_FILE_DIR:IRETests>/
    COMMAND $<TARGET_FILE:IRETests>
)

add_dependencies(IRERunTests IRETests)

set(TESTS_INSTALL_DESTINATION "./ire/$<CONFIG>/tests/")

install(TARGETS IRETests RUNTIME DESTINATION ${TESTS_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-graphics> DESTINATION ${TESTS_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-audio> DESTINATION ${TESTS_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-window> DESTINATION ${TESTS_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-system> DESTINATION ${TESTS_INSTALL_DESTINATION})
