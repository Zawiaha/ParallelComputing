// Matrix.cpp
#include "Matrix.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

namespace matrix {

    Matrix::Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data(rows* cols) {
        if (rows == 0 || cols == 0) {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= rows_ || j >= cols_) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[i * cols_ + j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= rows_ || j >= cols_) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[i * cols_ + j];
    }

    void Matrix::fillRandom(double min, double max) {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(static_cast<unsigned int>(seed));
        std::uniform_real_distribution<double> dist(min, max);

        std::generate(data.begin(), data.end(), [&]() { return dist(gen); });
    }

    void Matrix::fill(double value) {
        std::fill(data.begin(), data.end(), value);
    }

}