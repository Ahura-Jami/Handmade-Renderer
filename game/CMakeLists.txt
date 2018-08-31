cmake_minimum_required(VERSION 3.8.0)

#=======================================================================================================================
# Add Source and header files
#=======================================================================================================================
# Main Module
list(APPEND SOURCE_FILES source/main.cpp)
list(APPEND HEADER_FILES source/triangle.h)

mark_as_advanced(${SOURCE_FILES} ${HEADER_FILES})

#=======================================================================================================================
# Define a target. Link libraries and directories to it.
#=======================================================================================================================
add_executable(Game ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Game PRIVATE Engine)

#target_include_directories(Game PRIVATE source/public)
