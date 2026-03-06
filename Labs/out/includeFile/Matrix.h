// Matrix.h
#pragma once

#include <vector>
#include <cstddef>

namespace matrix {

    class Matrix {
    private:
        std::vector<double> data;
        size_t rows_;
        size_t cols_;

    public:
        Matrix(size_t rows, size_t cols);
        Matrix(const Matrix& other) = default;
        Matrix& operator=(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;

        size_t rows() const noexcept { return rows_; }
        size_t cols() const noexcept { return cols_; }
        size_t size() const noexcept { return data.size(); }

        double operator()(size_t i, size_t j) const;
        double& operator()(size_t i, size_t j);

        const double* raw_data() const noexcept { return data.data(); }
        double* raw_data() noexcept { return data.data(); }

        void fillRandom(double min = 0.0, double max = 100.0);
        void fill(double value);
        bool empty() const noexcept { return data.empty(); }
    };

}