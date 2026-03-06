// ParallelAlgorithm.cpp
#include "ParallelAlgorithm.h"
#include <limits>
#include <omp.h>
#include <sstream>

namespace matrix {

    ParallelAlgorithm::ParallelAlgorithm(int threads) : numThreads(threads) {
        if (threads > 0) {
            omp_set_num_threads(threads);
        }
    }

    void ParallelAlgorithm::setNumThreads(int threads) {
        numThreads = threads;
        if (threads > 0) {
            omp_set_num_threads(threads);
        }
    }

    int ParallelAlgorithm::getNumThreads() const {
        return numThreads > 0 ? numThreads : omp_get_max_threads();
    }

    std::string ParallelAlgorithm::name() const {
        std::ostringstream oss;
        oss << "Parallel (" << getNumThreads() << " threads)";
        return oss.str();
    }

    std::vector<double> ParallelAlgorithm::execute(const Matrix& matrix) {
        if (matrix.empty()) {
            return {};
        }

        size_t rows = matrix.rows();
        size_t cols = matrix.cols();

        std::vector<double> result(cols, std::numeric_limits<double>::lowest());

        #pragma omp parallel for
        for (int j = 0; j < static_cast<int>(cols); ++j) {
            double max_val = std::numeric_limits<double>::lowest();

            for (size_t i = 0; i < rows; ++i) {
                double value = matrix(i, j);
                if (value > max_val) {
                    max_val = value;
                }
            }

            result[j] = max_val;
        }

        return result;
    }

}