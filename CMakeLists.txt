cmake_minimum_required(VERSION 3.10)
project(NeuralNetwork CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/NeuralNetwork.cpp
    src/Matrix.cpp
)

add_executable(neural_network ${SOURCES})

set_target_properties(neural_network PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
