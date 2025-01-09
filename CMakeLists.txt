cmake_minimum_required(VERSION 3.10)
project(glamdoll)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include CMake's FetchContent module
include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 7b6aead
)
FetchContent_MakeAvailable(glfw)

# Fetch GLAD (Generated C OpenGL loader branch)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG 5bf3eda
)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0af55cc
)
FetchContent_MakeAvailable(glm)

# Define target executable
add_executable(glamdoll)

# Locate C/C++ source files
target_sources(glamdoll PRIVATE
  glamdoll/src/main.cpp
  glamdoll/src/shader.cpp
  ${glad_SOURCE_DIR}/src/glad.c
)

# Copy shader folder into to the build directory
add_custom_target(copy_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/glamdoll/shaders/
        ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/
)

# Link external library binaries
target_link_libraries(glamdoll PRIVATE glfw)

# Locate header file include directories
target_include_directories(glamdoll PRIVATE
  ${glad_SOURCE_DIR}/include
  ${glm_SOURCE_DIR}/
)
