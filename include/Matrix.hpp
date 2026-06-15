#pragma once

//  used for the neural network math

#include <vector>
#include <random>
#include <stdexcept>

class Matrix {
private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> data; // data[row][col]

public:
    // Empty matrix with no values
    Matrix();

    // Matrix with a fixed size, filled with zeros
    Matrix(size_t rows, size_t cols);

    // Build a matrix from existing 2D data
    Matrix(const std::vector<std::vector<double>>& data);

    // Get the number of rows and columns
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Read or write a value
    double get(size_t row, size_t col) const { return data[row][col]; }
    void set(size_t row, size_t col, double value) { data[row][col] = value; }

    // Matrix math for neural networks
    static Matrix multiply(const Matrix& a, const Matrix& b);
    static Matrix add(const Matrix& a, const Matrix& b);
    static Matrix subtract(const Matrix& a, const Matrix& b);
    Matrix transpose() const;
    Matrix elementwiseMultiply(const Matrix& other) const;

    // Helpers
    void randomize();
    void print() const;
    std::vector<double> toVector() const;
    static Matrix fromVector(const std::vector<double>& vec);
};
