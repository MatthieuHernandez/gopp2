cmake_minimum_required(VERSION 3.10)

project(gopp2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD  20)

include_directories(../cppfront/include)

include(FetchContent)

FetchContent_Declare(
  StraightforwardNeuralNetwork
  GIT_REPOSITORY https://github.com/MatthieuHernandez/StraightforwardNeuralNetwork.git
  GIT_TAG        v1.8.2)

FetchContent_MakeAvailable(StraightforwardNeuralNetwork)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Core Concurrent Widgets)

add_executable(gopp2 ./src/cpp1/cpp2_sources.cpp
                     ./src/cpp1/goban_widget.cpp
                     ./src/cpp1/learning_rate_box.cpp
                     ./src/cpp1/window.cpp
                     ./src/generated/main.cpp)

target_include_directories(gopp2 PRIVATE ./src/cpp1
                                         ./src/cpp2
                                         ./src/generated)

target_compile_options(gopp2 PRIVATE -w)
target_link_libraries(gopp2 PRIVATE Qt6::Concurrent Qt6::Widgets StraightforwardNeuralNetwork)
