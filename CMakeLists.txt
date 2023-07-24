cmake_minimum_required(VERSION 3.22)
project(GraphicsAlgorithms)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/lib/GLFW/include)

include_directories(${CMAKE_SOURCE_DIR}/lib/GLAD/include/glad)
include_directories(${CMAKE_SOURCE_DIR}/lib/GLAD/include/KHR)

add_executable(GraphicsAlgorithms src/main.cpp include/math/vec2.h src/windowHandler.cpp include/windowHandler.h include/algorithms/bezier.h include/math/badMath.h src/renderer.cpp include/renderer.h include/config.h include/algorithms/cubic.h include/algorithms/hermite.h include/math/array.h lib/GLAD/src/glad.c)
target_link_libraries(GraphicsAlgorithms OpenGL::GL)
target_link_libraries(GraphicsAlgorithms ${CMAKE_SOURCE_DIR}/lib/GLFW/glfw3.lib)