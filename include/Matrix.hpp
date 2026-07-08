#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

// basic matrix class, just a 2d grid of doubles
class Matrix {
public:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

    Matrix();
    Matrix(int r, int c);

    Matrix multiply(const Matrix &other);   // normal matrix multiplication
    Matrix transpose();                     // flip rows and columns
    void randomize();                       // fill with random values between -1 and 1
};

#endif
