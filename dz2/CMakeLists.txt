cmake_minimum_required(VERSION 3.8)
project(DZ2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -ggdb3 -fcoroutines -pthread")

set(CMAKE_CXX_STANDARD 17)

# LIBEVENT_INCLUDE
find_path(LIBEVENT_INCLUDE_DIR event.h
        PATHS
        /usr/local
        /opt
        PATH_SUFFIXES
        include
        )

find_library(LIBEVENT_LIB
        NAMES
        event
        PATHS
        /usr/local
        /opt
        PATH_SUFFIXES
        lib
        lib64
        )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
        LIBEVENT_LIB
        LIBEVENT_INCLUDE_DIR
)


# Request/Response realisation
add_library(http STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/http/request.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/http/response.cpp)

target_include_directories(http PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/http)

# Handler
add_library(handler STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/handler/handler.cpp)

target_include_directories(handler PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/handler
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(handler
        http)

# Server
add_library(server STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/server/server.cpp)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/server
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${LIBEVENT_INCLUDE_DIR})

target_link_libraries(server
        handler
        ${LIBEVENT_LIB})


# Main
add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(main PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(main
        server)


#Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest)
enable_testing()

add_executable(tests tests/http_request_tests.cpp)

target_include_directories(tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/http)

target_link_libraries(tests
        gtest_main
        http)