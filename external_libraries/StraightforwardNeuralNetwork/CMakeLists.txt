include(FetchContent)

FetchContent_Declare(
  StraightforwardNeuralNetwork
  GIT_REPOSITORY https://github.com/MatthieuHernandez/StraightforwardNeuralNetwork.git
  GIT_TAG        af53b5ee1d6f7c4d2ab80484231edab8ea6c672b # master
)

FetchContent_MakeAvailable(StraightforwardNeuralNetwork)
