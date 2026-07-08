# Neural Network

neural network written in c++ from scratch with no libraries.

## How to build

see HOW_TO_RUN.txt

## Description

builds a small network with 2 inputs, 4 hidden neurons, 1 output.
trains a neural network on XOR.
XOR means: inputs same = 0, inputs different = 1.

    0 XOR 0 = 0
    0 XOR 1 = 1
    1 XOR 0 = 1
    1 XOR 1 = 0

the network trains for 10000 epochs and should hit 100% accuracy.
MSE printed every 2000 epochs. lower is better. should approach 0.


## files

    src/main.cpp          - runs the XOR demo
    src/NeuralNetwork.cpp - forward pass, backprop, weight update
    src/Matrix.cpp        - matrix math
    include/              - headers for all of the above
