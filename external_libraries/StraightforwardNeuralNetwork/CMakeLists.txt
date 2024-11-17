include(FetchContent)

FetchContent_Declare(
  StraightforwardNeuralNetwork
  GIT_REPOSITORY https://github.com/MatthieuHernandez/StraightforwardNeuralNetwork.git
  GIT_TAG        bd59ea5e41190bbfe00932fd266c096bdb3c6bfd # master
)

FetchContent_MakeAvailable(StraightforwardNeuralNetwork)
