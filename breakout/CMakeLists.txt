cmake_minimum_required(VERSION 3.8.0)

#=======================================================================================================================
# Add Source and header files
#=======================================================================================================================
# Main Module
list(APPEND SOURCE_FILES source/game.cpp)
list(APPEND HEADER_FILES include/game.h)

mark_as_advanced(${SOURCE_FILES} ${HEADER_FILES})

#=======================================================================================================================
# Define a target. Link libraries and directories to it.
#=======================================================================================================================
add_executable(Breakout ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Breakout PRIVATE Engine)

#=======================================================================================================================
# Define macros
#=======================================================================================================================
#target_compile_definitions(Game PRIVATE PROJECT_DIR="${CMAKE_SOURCE_DIR}/")
