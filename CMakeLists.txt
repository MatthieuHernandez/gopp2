cmake_minimum_required(VERSION 3.10)

project(gopp2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD  20)

include_directories(../cppfront/include)

include(FetchContent)

FetchContent_Declare(
  StraightforwardNeuralNetwork
  GIT_REPOSITORY https://github.com/MatthieuHernandez/StraightforwardNeuralNetwork.git
  GIT_TAG        5ab3e039f9fa1295964bb7967d68ae6474833b36 # master
)

FetchContent_MakeAvailable(StraightforwardNeuralNetwork)


add_executable(gopp2 ./generate/main.cpp)

target_link_libraries(gopp2 StraightforwardNeuralNetwork)

