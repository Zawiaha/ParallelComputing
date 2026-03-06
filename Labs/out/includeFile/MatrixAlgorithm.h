// MatrixAlgorithm.h
#pragma once

#include "Matrix.h"
#include <vector>
#include <string>

namespace matrix {

    class MatrixAlgorithm {
    public:
        virtual ~MatrixAlgorithm() = default;
        virtual std::vector<double> execute(const Matrix& matrix) = 0;
        virtual std::string name() const = 0;
    };

}
