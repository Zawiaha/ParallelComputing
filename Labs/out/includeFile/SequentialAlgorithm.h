// SequentialAlgorithm.h
#pragma once

#include "MatrixAlgorithm.h"

namespace matrix {

    class SequentialAlgorithm : public MatrixAlgorithm {
    public:
        std::vector<double> execute(const Matrix& matrix) override;
        std::string name() const override { return "Sequential"; }
    };

}
