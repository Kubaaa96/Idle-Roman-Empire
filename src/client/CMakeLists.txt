cmake_minimum_required(VERSION 3.1)

project(IREClient)

file(GLOB_RECURSE CORE_SOURCES "*.cpp")

add_executable(IREClient ${CORE_SOURCES})

set_property(TARGET IREClient PROPERTY CXX_STANDARD 17)
set_property(TARGET IREClient PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(IREClient PRIVATE Threads::Threads)
target_link_libraries(IREClient PRIVATE IRECore)
target_link_libraries(IREClient PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

set(CLIENT_INSTALL_DESTINATION "./ire/$<CONFIG>/client/")

install(TARGETS IREClient RUNTIME DESTINATION ${CLIENT_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-graphics> DESTINATION ${CLIENT_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-audio> DESTINATION ${CLIENT_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-window> DESTINATION ${CLIENT_INSTALL_DESTINATION})
install(FILES $<TARGET_FILE:sfml-system> DESTINATION ${CLIENT_INSTALL_DESTINATION})
