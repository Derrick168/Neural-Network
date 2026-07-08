#include "NeuralNetwork.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));  // so the starting weights are different every run

    cout << "Neural Network XOR Demo" << endl;
    cout << "======================" << endl;

    // 2 inputs -> 4 hidden neurons -> 1 output
    NeuralNetwork nn(0.5);
    nn.addLayer(2, 4);
    nn.addLayer(4, 1);

    cout << "Created network with 2->4->1 structure." << endl;
    nn.printArchitecture();

    // the 4 possible XOR inputs and their answers
    vector<vector<double>> inputs = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    vector<vector<double>> targets = {
        {0},
        {1},
        {1},
        {0}
    };

    int epochs = 10000;
    cout << "Training for " << epochs << " epochs..." << endl;

    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int i = 0; i < 4; i++) {
            nn.train(inputs[i], targets[i]);
        }

        // print the error every 2000 epochs so we can see it going down
        if ((epoch + 1) % 2000 == 0) {
            double totalError = 0;
            for (int i = 0; i < 4; i++) {
                vector<double> output = nn.predict(inputs[i]);
                double diff = output[0] - targets[i][0];
                totalError += diff * diff;
            }
            cout << "Epoch " << (epoch + 1) << "/" << epochs
                 << " - MSE=" << totalError / 4 << endl;
        }
    }

    cout << "Training complete." << endl;
    cout << "\nTesting network on XOR inputs:" << endl;

    int correct = 0;
    for (int i = 0; i < 4; i++) {
        vector<double> output = nn.predict(inputs[i]);
        double value = output[0];

        // round the output to 0 or 1
        int predicted = 0;
        if (value > 0.5) {
            predicted = 1;
        }

        int expected = (int)targets[i][0];
        if (predicted == expected) {
            correct++;
        }

        cout << (int)inputs[i][0] << " XOR " << (int)inputs[i][1]
             << " -> " << value << " (expected " << expected << ")" << endl;
    }

    double accuracy = correct / 4.0 * 100.0;
    cout << "\nAccuracy: " << accuracy << "%" << endl;

    if (accuracy >= 99.0) {
        cout << "Network learned XOR strongly." << endl;
    } else {
        cout << "Network did not learn XOR perfectly yet." << endl;
    }

    return 0;
}
