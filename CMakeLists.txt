cmake_minimum_required(VERSION 3.31.6)
project(LearnOpenGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(learn-opengl src/main.cpp)
target_link_libraries(learn-opengl SDL3)
