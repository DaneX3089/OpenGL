cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# ================================
# Include directories
# ================================
include_directories(
    glad/include
    libs/glfw/include
)

# ================================
# Link directories (for precompiled glfw)
# ================================
link_directories(
    libs/glfw/lib-mingw-w64
)

# ================================
# Source files
# ================================
add_executable(OpenGLProject
    src/shader.h
    src/main.cpp
    src/gl.c        # GLAD C file
)

# ================================
# Link libraries
# ================================
target_link_libraries(OpenGLProject
    glfw3
    opengl32
)
