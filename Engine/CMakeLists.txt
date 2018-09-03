cmake_minimum_required(VERSION 3.8.0)

project(Engine VERSION 0.0.1)

#=======================================================================================================================
# Add Source and header files
#=======================================================================================================================
list(APPEND ENGINE_HEADERS Include/Engine.h)
list(APPEND ENGINE_SOURCES Source/Engine.cpp)

list(APPEND ENGINE_HEADERS Include/Types.h)
list(APPEND ENGINE_HEADERS Include/Actor.h)

list(APPEND ENGINE_HEADERS Include/Shader.h)
list(APPEND ENGINE_SOURCES Source/Shader.cpp)

list(APPEND ENGINE_HEADERS Include/Camera.h)
list(APPEND ENGINE_SOURCES Source/Camera.cpp)

list(APPEND ENGINE_HEADERS Include/Texture.h)
list(APPEND ENGINE_SOURCES Source/Texture.cpp)

list(APPEND ENGINE_HEADERS Include/ResourceManager.h)
list(APPEND ENGINE_SOURCES Source/ResourceManager.cpp)

list(APPEND ENGINE_HEADERS Include/Math.h)

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
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Source)

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
add_subdirectory(ThirdParty/glfw)
#find_package(glfw REQUIRED HINTS thirdparty/glfw/CMake)
target_link_libraries(Engine PUBLIC glfw)

# force off glfw's examples and tests
set(GLFW_BUILD_EXAMPLES  OFF  CACHE  BOOL  "Build the GLFW example programs"  FORCE)
set(GLFW_BUILD_TESTS     OFF  CACHE  BOOL  "Build the GLFW test programs"     FORCE)
set(GLFW_BUILD_DOCS      OFF  CACHE  BOOL  "Build the GLFW documentation"     FORCE)
set(GLFW_INSTALL         OFF  CACHE  BOOL  "Generate installation target"     FORCE)

# GLAD
target_include_directories(Engine PUBLIC ThirdParty/glad/include)
target_sources(Engine PRIVATE ThirdParty/glad/src/glad.c)

# STB_IMAGE
target_include_directories(Engine PUBLIC ThirdParty/stb/include)
target_sources(Engine PRIVATE ThirdParty/stb/src/stb_image.cpp)

# GLM
#find_package(glm REQUIRED)
add_subdirectory(ThirdParty/glm)
target_link_libraries(Engine PUBLIC glm)
set(GLM_TEST_ENABLE  OFF  CACHE  BOOL  "Build unit tests"  FORCE)

#=======================================================================================================================
# Enable unit tests
#=======================================================================================================================
add_subdirectory(Test)
