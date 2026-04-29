#pragma once

#include "MatrixAlgorithm.h"

namespace matrix {

    class CUDAAlgorithm : public MatrixAlgorithm {
    public:
        CUDAAlgorithm() = default;
        ~CUDAAlgorithm() = default;

        std::vector<double> execute(const Matrix& matrix) override;
        std::string name() const override;
        
        static bool isAvailable();
    };

}