#include "NeuralNetwork.hpp"
#include <iostream>

using namespace std;

NeuralNetwork::NeuralNetwork(double lr) {
    learningRate = lr;
}

void NeuralNetwork::addLayer(int inputSize, int outputSize) {
    Layer layer;
    layer.weights = Matrix(outputSize, inputSize);
    layer.biases = Matrix(outputSize, 1);
    layer.error = Matrix(outputSize, 1);
    layer.weights.randomize();
    layer.biases.randomize();
    layers.push_back(layer);
}

void NeuralNetwork::train(const vector<double> &input, const vector<double> &target) {
    forward(input);
    backward(target);
    updateWeights();
}

vector<double> NeuralNetwork::predict(const vector<double> &input) {
    forward(input);

    // turn the last layers output back into a normal vector
    vector<double> result;
    Matrix &out = layers.back().output;
    for (int i = 0; i < out.rows; i++) {
        result.push_back(out.data[i][0]);
    }
    return result;
}

void NeuralNetwork::forward(const vector<double> &input) {
    // turn the input into a column matrix
    Matrix current((int)input.size(), 1);
    for (int i = 0; i < (int)input.size(); i++) {
        current.data[i][0] = input[i];
    }

    for (int i = 0; i < (int)layers.size(); i++) {
        layers[i].input = current;  // save it for backprop later

        // z = weights * input, then add bias and apply sigmoid
        Matrix z = layers[i].weights.multiply(current);
        for (int j = 0; j < z.rows; j++) {
            z.data[j][0] = sigmoid(z.data[j][0] + layers[i].biases.data[j][0]);
        }

        layers[i].output = z;
        current = z;  // this layers output is the next layers input
    }
}

void NeuralNetwork::backward(const vector<double> &target) {
    int last = (int)layers.size() - 1;

    // output layer: error = (output - target) * sigmoid'(output)
    for (int i = 0; i < layers[last].output.rows; i++) {
        double out = layers[last].output.data[i][0];
        layers[last].error.data[i][0] = (out - target[i]) * sigmoidDerivative(out);
    }

    // hidden layers: send the error backwards through the weights
    for (int i = last - 1; i >= 0; i--) {
        Matrix wt = layers[i + 1].weights.transpose();
        Matrix passedBack = wt.multiply(layers[i + 1].error);

        for (int j = 0; j < layers[i].output.rows; j++) {
            double out = layers[i].output.data[j][0];
            layers[i].error.data[j][0] = passedBack.data[j][0] * sigmoidDerivative(out);
        }
    }
}

void NeuralNetwork::updateWeights() {
    for (int i = 0; i < (int)layers.size(); i++) {
        Layer &layer = layers[i];

        // move each weight a little bit against its gradient
        for (int r = 0; r < layer.weights.rows; r++) {
            for (int c = 0; c < layer.weights.cols; c++) {
                layer.weights.data[r][c] -= learningRate * layer.error.data[r][0] * layer.input.data[c][0];
            }
            layer.biases.data[r][0] -= learningRate * layer.error.data[r][0];
        }
    }
}

void NeuralNetwork::printArchitecture() {
    cout << "Network layers: " << layers.size() << endl;
    cout << "Learning rate: " << learningRate << endl;
    for (int i = 0; i < (int)layers.size(); i++) {
        cout << " Layer " << i + 1 << ": " << layers[i].weights.cols
             << " -> " << layers[i].weights.rows << " (sigmoid)" << endl;
    }
}
