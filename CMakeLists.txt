cmake_minimum_required(VERSION 3.13)
project(openGL_Project)
set(CMAKE_CXX_STANDARD 14)

# GLAD as its own library
add_library(glad src/gl.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/glad/include)

# 👇 ensure glad is compiled with -fPIC
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Main executable
add_executable(openGL_Project
    src/main.cpp
    src/stb_image.cpp
    src/stb_image.h
)

target_include_directories(openGL_Project
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(openGL_Project
    PRIVATE
        glfw
        glad
)
