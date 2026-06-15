#pragma once

#include "Matrix.hpp"
#include "Activation.hpp"
#include <vector>

// Simple neural network class. stores trains layers.
class NeuralNetwork {
private:
    struct Layer {
        Matrix weights;
        Matrix biases;
        Matrix inputs;
        Matrix outputs;
        Matrix errors;
        ActivationType activation;

        Layer(size_t inputSize, size_t outputSize, ActivationType act = ActivationType::SIGMOID);
    };

    std::vector<Layer> layers;
    double learningRate;

public:
    NeuralNetwork(double learningRate = 0.1);

    // Add a layer: inputSize -> outputSize
    void addLayer(size_t inputSize, size_t outputSize, ActivationType activation = ActivationType::SIGMOID);

    // Predict from input values
    std::vector<double> predict(const std::vector<double>& input);

    // Train on one example for some epochs
    void train(const std::vector<double>& input, const std::vector<double>& target, int epochs = 1);

    // Get the current output from the network
    std::vector<double> getOutput() const;

    size_t getLayerCount() const { return layers.size(); }
    double getLearningRate() const { return learningRate; }
    void setLearningRate(double lr) { learningRate = lr; }

    void printArchitecture() const;

private:
    void forward(const std::vector<double>& input);
    void backward(const std::vector<double>& target);
    void updateWeights();
};

