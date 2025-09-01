cmake_minimum_required(VERSION 3.13)
project(openGL_Project)
set(CMAKE_CXX_STANDARD 14)

# Ensure position independent code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOURCE_FILES
    src/main.cpp
    src/gl.c   # GLAD loader
    src/stb_image.cpp
    src/stb_image.h
)

add_executable(openGL_Project ${SOURCE_FILES})

target_include_directories(openGL_Project
    PRIVATE
        ${CMAKE_SOURCE_DIR}/glad/include
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(openGL_Project glfw)
