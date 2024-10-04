cmake_minimum_required(VERSION 3.5)

project(gopp2)

set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD  20)

include_directories(./src)
include_directories(../cppfront/include)

add_executable(gopp2
    ./src/io.cpp
    ./generate/main.cpp)

    