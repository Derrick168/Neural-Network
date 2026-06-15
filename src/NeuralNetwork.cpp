#include "NeuralNetwork.hpp"
#include <iostream>

NeuralNetwork::Layer::Layer(size_t inputSize, size_t outputSize, ActivationType act)
    : weights(outputSize, inputSize),
      biases(outputSize, 1),
      inputs(inputSize, 1),
      outputs(outputSize, 1),
      errors(outputSize, 1),
      activation(act) {
    weights.randomize();
    biases.randomize();
}

NeuralNetwork::NeuralNetwork(double lr) : learningRate(lr) {}

void NeuralNetwork::addLayer(size_t inputSize, size_t outputSize, ActivationType activation) {
    if (!layers.empty() && layers.back().weights.getRows() != inputSize) {
        throw std::invalid_argument("Layer input size must match previous layer output size");
    }
    Layer newlayer(inputSize, outputSize, activation);
    layers.push_back(newlayer);
}

std::vector<double> NeuralNetwork::predict(const std::vector<double>& input) {
    forward(input);
    return getOutput();
}

std::vector<double> NeuralNetwork::getOutput() const {
    if (layers.empty()) {
        throw std::runtime_error("Network has no layers");
    }
    return layers.back().outputs.toVector();
}

void NeuralNetwork::train(const std::vector<double>& input, const std::vector<double>& target, int epochs) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        forward(input);
        backward(target);
        updateWeights();
    }
}

void NeuralNetwork::forward(const std::vector<double>& input) {
    if (layers.empty()) {
        throw std::runtime_error("Network has no layers");
    }

    Matrix cur = Matrix::fromVector(input); //convert input vec to column matrix
    for (size_t i = 0; i < layers.size(); ++i) {
        Layer& layer = layers[i];
        layer.inputs = cur; //store input for backprop later

        Matrix z = Matrix::multiply(layer.weights, cur); //w*x
        z = Matrix::add(z, layer.biases); //w*x + b

        for (size_t j = 0; j < z.getRows(); ++j) { //apply activation to each element
            z.set(j, 0, activate(z.get(j, 0), layer.activation));
        }
        layer.outputs = z;
        cur = layer.outputs; //output of this layer is input to next
    }
}

void NeuralNetwork::backward(const std::vector<double>& target) {
    if (layers.empty()) {
        throw std::runtime_error("Network has no layers");
    }

    Matrix targetmat = Matrix::fromVector(target);
    Layer& outlayer = layers.back();

    //output layer error = (output - target) * f'(output)
    Matrix outerr = Matrix::subtract(outlayer.outputs, targetmat);
    Matrix outderiv(outlayer.outputs.getRows(), 1);
    for (size_t i = 0; i < outlayer.outputs.getRows(); ++i) {
        outderiv.set(i, 0, derivative(outlayer.outputs.get(i, 0), outlayer.activation));
    }
    outlayer.errors = outerr.elementwiseMultiply(outderiv);

    //propagate error back through hidden layers
    for (int i = (int)layers.size() - 2; i >= 0; --i) {
        Layer& cur = layers[i];
        Layer& next = layers[i + 1];

        Matrix wt = next.weights.transpose();
        Matrix properr = Matrix::multiply(wt, next.errors); //w^T * next_errors

        Matrix deriv(cur.outputs.getRows(), 1);
        for (size_t j = 0; j < cur.outputs.getRows(); ++j) {
            deriv.set(j, 0, derivative(cur.outputs.get(j, 0), cur.activation));
        }
        cur.errors = properr.elementwiseMultiply(deriv);
    }
}

void NeuralNetwork::updateWeights() {
    for (size_t i = 0; i < layers.size(); ++i) {
        Layer& layer = layers[i];
        Matrix wgrad = Matrix::multiply(layer.errors, layer.inputs.transpose()); //delta * input^T

        for (size_t r = 0; r < layer.weights.getRows(); ++r) {
            for (size_t c = 0; c < layer.weights.getCols(); ++c) {
                double w = layer.weights.get(r, c);
                layer.weights.set(r, c, w - learningRate * wgrad.get(r, c));
            }
        }
        for (size_t r = 0; r < layer.biases.getRows(); ++r) {
            double b = layer.biases.get(r, 0);
            layer.biases.set(r, 0, b - learningRate * layer.errors.get(r, 0));
        }
    }
}

void NeuralNetwork::printArchitecture() const {
    std::cout << "Network layers: " << layers.size() << "\n";
    std::cout << "Learning rate: " << learningRate << "\n";
    for (size_t i = 0; i < layers.size(); ++i) {
        std::cout << " Layer " << i + 1 << ": "
                  << layers[i].weights.getCols() << " -> "
                  << layers[i].weights.getRows();
        if (layers[i].activation == ActivationType::SIGMOID) std::cout << " (Sigmoid)";
        if (layers[i].activation == ActivationType::RELU)    std::cout << " (ReLU)";
        if (layers[i].activation == ActivationType::TANH)    std::cout << " (Tanh)";
        std::cout << "\n";
    }
}
