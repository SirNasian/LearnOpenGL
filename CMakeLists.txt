cmake_minimum_required(VERSION 3.31.6)
project(LearnOpenGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LEARNOPENGL_SOURCES "learnopengl/src/*.c" "learnopengl/src/*.cpp" "vendor/*.c" "vendor/*.cpp")
add_executable(learn-opengl ${LEARNOPENGL_SOURCES})
target_include_directories(learn-opengl PRIVATE vendor/glad/include)
target_link_libraries(learn-opengl SDL3)
