#=======================================================================================================================
# Project Setup
#=======================================================================================================================
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Global project name
project(ENGINE VERSION 0.0.1 LANGUAGES C CXX)

# Version preprocessor.
add_compile_definitions(ENGINE_VERSION="0.0.1")

# C++ Version
set(CMAKE_CXX_STANDARD 17)

# Tell CMake not to define WIN32 when building with Cygwin.
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

#=======================================================================================================================
# Add subdirectories
#=======================================================================================================================
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(breakout)



