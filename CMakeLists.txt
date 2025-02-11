cmake_minimum_required(VERSION 3.10)

project(gopp2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD  20)

include_directories(../cppfront/include)

include(FetchContent)

FetchContent_Declare(
  StraightforwardNeuralNetwork
  GIT_REPOSITORY https://github.com/MatthieuHernandez/StraightforwardNeuralNetwork.git
  GIT_TAG        a18bdb627f5e4c7757f404489f42070f99e85635 # master
)

FetchContent_MakeAvailable(StraightforwardNeuralNetwork)


add_executable(gopp2 ./generate/main.cpp)

target_compile_options(gopp2 PRIVATE -w)
target_link_libraries(gopp2 StraightforwardNeuralNetwork)

