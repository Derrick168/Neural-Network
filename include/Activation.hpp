#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <cmath>

// sigmoid squashes any number into a value between 0 and 1
inline double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// derivative of sigmoid, y here is already sigmoid(x)
inline double sigmoidDerivative(double y) {
    return y * (1.0 - y);
}

#endif
