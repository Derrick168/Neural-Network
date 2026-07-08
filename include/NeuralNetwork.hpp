#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Matrix.hpp"
#include "Activation.hpp"
#include <vector>

// a simple feed forward neural network trained with backpropagation
class NeuralNetwork {
public:
    NeuralNetwork(double lr);

    void addLayer(int inputSize, int outputSize);
    void train(const std::vector<double> &input, const std::vector<double> &target);
    std::vector<double> predict(const std::vector<double> &input);
    void printArchitecture();

private:
    // one layer of the network
    struct Layer {
        Matrix weights;
        Matrix biases;
        Matrix input;   // input saved from the forward pass
        Matrix output;  // output saved from the forward pass
        Matrix error;   // how wrong each neuron was
    };

    std::vector<Layer> layers;
    double learningRate;

    void forward(const std::vector<double> &input);
    void backward(const std::vector<double> &target);
    void updateWeights();
};

#endif
