#include "Matrix.hpp"
#include <cstdlib>
#include <iostream>

Matrix::Matrix() {
    rows = 0;
    cols = 0;
}

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    // start everything at zero
    for (int i = 0; i < rows; i++) {
        std::vector<double> row(cols, 0.0);
        data.push_back(row);
    }
}

Matrix Matrix::multiply(const Matrix &other) {
    if (cols != other.rows) {
        std::cout << "ERROR: matrix sizes dont match for multiply" << std::endl;
        exit(1);
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            double sum = 0;
            for (int k = 0; k < cols; k++) {
                sum = sum + data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

Matrix Matrix::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

void Matrix::randomize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // rand() gives 0 to RAND_MAX, this scales it to -1 to 1
            data[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }
}
