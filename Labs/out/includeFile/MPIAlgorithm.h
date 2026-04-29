#pragma once

#include "MatrixAlgorithm.h"
#include <mpi.h>

namespace matrix {

    class MPIAlgorithm : public MatrixAlgorithm {
    private:
        int rank;
        int size;

    public:
        MPIAlgorithm();
        ~MPIAlgorithm() = default;

        std::vector<double> execute(const Matrix& matrix) override;
        std::string name() const override;
    };

}