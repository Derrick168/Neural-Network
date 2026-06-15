#pragma once
#include <cmath>

// activation types the network can use
enum class ActivationType {
    SIGMOID,
    RELU,
    TANH
};

// sigmoid and its derivative (takes output, not raw input)
inline double sigmoid(double x)         { return 1.0 / (1.0 + std::exp(-x)); }
inline double sigmoid_deriv(double out) { return out * (1.0 - out); }

// relu and its derivative
inline double relu(double x)            { return x > 0 ? x : 0.0; }
inline double relu_deriv(double out)    { return out > 0 ? 1.0 : 0.0; }

// tanh and its derivative
inline double tanh_act(double x)        { return std::tanh(x); }
inline double tanh_deriv(double out)    { return 1.0 - out * out; }

// pick the right activation based on type
inline double activate(double x, ActivationType type) {
    if (type == ActivationType::SIGMOID) return sigmoid(x);
    if (type == ActivationType::RELU)    return relu(x);
    if (type == ActivationType::TANH)    return tanh_act(x);
    return x;
}

// pick the right derivative based on type
inline double derivative(double out, ActivationType type) {
    if (type == ActivationType::SIGMOID) return sigmoid_deriv(out);
    if (type == ActivationType::RELU)    return relu_deriv(out);
    if (type == ActivationType::TANH)    return tanh_deriv(out);
    return 1.0;
}
