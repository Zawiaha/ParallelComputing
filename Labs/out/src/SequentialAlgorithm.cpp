#include "SequentialAlgorithm.h"
#include <limits>

namespace matrix {

    std::vector<double> SequentialAlgorithm::execute(const Matrix& matrix) {
        if (matrix.empty()) {
            return {};
        }

        size_t rows = matrix.rows();
        size_t cols = matrix.cols();

        std::vector<double> result(cols, std::numeric_limits<double>::lowest());

        for (size_t j = 0; j < cols; ++j) {
            for (size_t i = 0; i < rows; ++i) {
                double value = matrix(i, j);
                if (value > result[j]) {
                    result[j] = value;
                }
            }
        }

        return result;
    }

}