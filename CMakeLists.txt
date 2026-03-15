cmake_minimum_required(VERSION 3.20)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

add_executable(OpenGL src/main.cpp vendor/glad/src/gl.c
        core/Application.cpp
        core/Application.h
        core/VAO.cpp
        core/VAO.h
        core/VBO.cpp
        core/VBO.h
        core/EBO.cpp
        core/EBO.h
        core/Shader.h
)

target_include_directories(OpenGL PRIVATE
        vendor/glad/include
)

target_link_libraries(OpenGL glfw glm opengl32)