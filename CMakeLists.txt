cmake_minimum_required(VERSION 3.5)

project(gopp2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD  20)

include_directories(../cppfront/include)

include(FetchContent)

FetchContent_Declare(
  StraightforwardNeuralNetwork
  GIT_REPOSITORY https://github.com/MatthieuHernandez/StraightforwardNeuralNetwork.git
  GIT_TAG        af53b5ee1d6f7c4d2ab80484231edab8ea6c672b # master
)

FetchContent_MakeAvailable(StraightforwardNeuralNetwork)


add_executable(gopp2 ./generate/main.cpp)

target_link_libraries(gopp2 StraightforwardNeuralNetwork)
