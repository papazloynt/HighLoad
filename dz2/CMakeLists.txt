cmake_minimum_required(VERSION 3.8)
project(DZ2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -ggdb3 ")

set(CMAKE_CXX_STANDARD 17)

# Main
add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)