#include "NeuralNetwork.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    std::cout << "Neural Network XOR Demo" << std::endl;
    std::cout << "======================" << std::endl;

    NeuralNetwork nn(0.5);
    nn.addLayer(2, 4, ActivationType::SIGMOID);
    nn.addLayer(4, 1, ActivationType::SIGMOID);

    std::cout << "Created network with 2->4->1 structure." << std::endl;
    nn.printArchitecture();

    std::vector<std::vector<double>> inputs = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}
    };

    std::vector<std::vector<double>> targets = {
        {0.0},
        {1.0},
        {1.0},
        {0.0}
    };

    int epochs = 10000;
    std::cout << "Training for " << epochs << " epochs..." << std::endl;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            nn.train(inputs[i], targets[i], 1);
        }

        if ((epoch + 1) % 2000 == 0) {
            double totalError = 0.0;
            for (size_t i = 0; i < inputs.size(); ++i) {
                auto output = nn.predict(inputs[i]);
                double diff = output[0] - targets[i][0];
                totalError += diff * diff;
            }
            totalError /= inputs.size();
            std::cout << "Epoch " << (epoch + 1) << "/" << epochs
                      << " - MSE=" << std::fixed << std::setprecision(6)
                      << totalError << std::endl;
        }
    }

    std::cout << "Training complete." << std::endl;
    std::cout << "\nTesting network on XOR inputs:\n" << std::endl;

    std::cout << std::left
              << std::setw(10) << "Input"
              << std::setw(10) << "Expected"
              << std::setw(10) << "Output" << "\n";
    std::cout << "------------------------------\n";

    int correct = 0;
    for (size_t i = 0; i < inputs.size(); ++i) {
        auto output = nn.predict(inputs[i]);
        double value = output[0];
        int predicted = value > 0.5 ? 1 : 0;
        int expect = static_cast<int>(targets[i][0]);

        if (predicted == expect) {
            correct++;
        }

        std::string inputStr = std::to_string(static_cast<int>(inputs[i][0]))
                             + " " + std::to_string(static_cast<int>(inputs[i][1]));
        std::cout << std::left
                  << std::setw(10) << inputStr
                  << std::setw(10) << expect
                  << std::fixed << std::setprecision(4) << value << "\n";
    }

    double accuracy = (static_cast<double>(correct) / inputs.size()) * 100.0;
    std::cout << "\nAccuracy: " << std::fixed << std::setprecision(1)
              << accuracy << "%" << std::endl;

    if (accuracy >= 99.0) {
        std::cout << "Network learned XOR strongly." << std::endl;
    } else {
        std::cout << "Network did not learn XOR perfectly yet." << std::endl;
    }

    return 0;
}

