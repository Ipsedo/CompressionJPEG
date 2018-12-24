cmake_minimum_required(VERSION 3.5)

project(CompressionJPEG C CXX)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SRC "src/*.h" "src/*.cpp" "src/*.c")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(CompressionJPEG ${SRC})
