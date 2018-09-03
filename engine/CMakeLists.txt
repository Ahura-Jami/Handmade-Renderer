cmake_minimum_required(VERSION 3.8.0)

project(Engine VERSION 0.0.1)

#=======================================================================================================================
# Add Source and header files
#=======================================================================================================================
list(APPEND ENGINE_HEADERS include/engine.h)
list(APPEND ENGINE_SOURCES source/engine.cpp)

list(APPEND ENGINE_HEADERS include/types.h)
list(APPEND ENGINE_HEADERS include/actor.h)

list(APPEND ENGINE_HEADERS include/shader.h)
list(APPEND ENGINE_SOURCES source/shader.cpp)

list(APPEND ENGINE_HEADERS include/camera.h)
list(APPEND ENGINE_SOURCES source/camera.cpp)

list(APPEND ENGINE_HEADERS include/texture.h)
list(APPEND ENGINE_SOURCES source/texture.cpp)

list(APPEND ENGINE_HEADERS include/resource_manager.h)
list(APPEND ENGINE_SOURCES source/resource_manager.cpp)

list(APPEND ENGINE_HEADERS include/emath.h)



#=======================================================================================================================
# Define the target and add all source and header files to it
#=======================================================================================================================
add_library(Engine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(Engine::Engine ALIAS Engine)

# Set the include directories for building and installation of Xenos
target_include_directories(Engine
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/source)

#=======================================================================================================================
# Set up options, properties and dependencies
#=======================================================================================================================
# Set language standard
#target_compile_features(Xenos
#    PRIVATE
#        cxx_std_17)

# Add compile flags
if (GNU)
    target_compile_options(Engine
            PRIVATE
                $<$<CXX_COMPILER_ID:GNU>:-Wall>)
endif()

#=======================================================================================================================
# Add thirdparty libraries
#=======================================================================================================================

# GLFW
add_subdirectory(thirdparty/glfw)
#find_package(glfw REQUIRED HINTS thirdparty/glfw/CMake)
target_link_libraries(Engine PUBLIC glfw)

# force off glfw's examples and tests
set(GLFW_BUILD_EXAMPLES  OFF  CACHE  BOOL  "Build the GLFW example programs"  FORCE)
set(GLFW_BUILD_TESTS     OFF  CACHE  BOOL  "Build the GLFW test programs"     FORCE)
set(GLFW_BUILD_DOCS      OFF  CACHE  BOOL  "Build the GLFW documentation"     FORCE)
set(GLFW_INSTALL         OFF  CACHE  BOOL  "Generate installation target"     FORCE)

# GLAD
target_include_directories(Engine PUBLIC thirdparty/glad/include)
target_sources(Engine PRIVATE thirdparty/glad/src/glad.c)

# STB_IMAGE
target_include_directories(Engine PUBLIC thirdparty/stb/include)
target_sources(Engine PRIVATE thirdparty/stb/src/stb_image.cpp)

# GLM
find_package(glm REQUIRED)
target_link_libraries(Engine PUBLIC glm)


#=======================================================================================================================
# Enable unit tests
#=======================================================================================================================
add_subdirectory(test)
