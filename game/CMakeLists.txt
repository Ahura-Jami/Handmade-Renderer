cmake_minimum_required(VERSION 3.8.0)

#=======================================================================================================================
# Add Source and header files
#=======================================================================================================================
# Main Module
list(APPEND SOURCE_FILES source/main.cpp)
list(APPEND HEADER_FILES source/triangle.h)
list(APPEND HEADER_FILES source/rectangle.h)

mark_as_advanced(${SOURCE_FILES} ${HEADER_FILES})

#=======================================================================================================================
# Define a target. Link libraries and directories to it.
#=======================================================================================================================
add_executable(Game ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Game PRIVATE Engine)

#=======================================================================================================================
# Define macros
#=======================================================================================================================
target_compile_definitions(Game PRIVATE PROJECT_DIR="${CMAKE_SOURCE_DIR}/")
