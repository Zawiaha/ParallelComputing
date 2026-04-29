#include "MPIAlgorithm.h"
#include <limits>
#include <sstream>
#include <vector>
#include <iostream>

namespace matrix {

    MPIAlgorithm::MPIAlgorithm() {
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
    }

    std::string MPIAlgorithm::name() const {
        std::ostringstream oss;
        oss << "MPI (" << size << " procs)";
        return oss.str();
    }

    std::vector<double> MPIAlgorithm::execute(const Matrix& matrix) {
        size_t rows = matrix.rows();
        size_t cols = matrix.cols();

        std::vector<double> result;

        if (rank == 0) {
            result.resize(cols, std::numeric_limits<double>::lowest());
        }


        MPI_Bcast(const_cast<double*>(matrix.raw_data()), rows * cols,
            MPI_DOUBLE, 0, MPI_COMM_WORLD);


        int cols_per_proc = cols / size;
        int start_col = rank * cols_per_proc;
        int end_col = (rank == size - 1) ? cols : start_col + cols_per_proc;

        std::vector<double> local_result(cols, std::numeric_limits<double>::lowest());

        for (int j = start_col; j < end_col; ++j) {
            double max_val = std::numeric_limits<double>::lowest();
            for (size_t i = 0; i < rows; ++i) {
                double val = matrix(i, j);
                if (val > max_val) max_val = val;
            }
            local_result[j] = max_val;
        }

        if (rank == 0) {
            MPI_Reduce(MPI_IN_PLACE, local_result.data(), cols, MPI_DOUBLE,
                MPI_MAX, 0, MPI_COMM_WORLD);
            result = local_result;
        }
        else {
            MPI_Reduce(local_result.data(), NULL, cols, MPI_DOUBLE,
                MPI_MAX, 0, MPI_COMM_WORLD);
        }

        return result;
    }

}