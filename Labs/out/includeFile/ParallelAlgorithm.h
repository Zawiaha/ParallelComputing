// ParallelAlgorithm.h
#pragma once

#include "MatrixAlgorithm.h"

namespace matrix {

    class ParallelAlgorithm : public MatrixAlgorithm {
    private:
        int numThreads;

    public:
        explicit ParallelAlgorithm(int threads = 0);

        std::vector<double> execute(const Matrix& matrix) override;
        std::string name() const override;

        void setNumThreads(int threads);
        int getNumThreads() const;
    };

}
