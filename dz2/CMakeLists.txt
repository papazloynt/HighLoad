cmake_minimum_required(VERSION 3.8)
project(DZ2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -ggdb3 -fcoroutines -pthread")

set(CMAKE_CXX_STANDARD 17)

# Request/Response realisation
add_library(http STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/http/request.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/http/response.cpp)

target_include_directories(http PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/http)


# Main
add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)


#Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest)
enable_testing()

add_executable(tests tests/http_request_tests.cpp)

target_include_directories(tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/http)

target_link_libraries(tests
        gtest_main
        http)