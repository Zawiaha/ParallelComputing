#include "CUDAAlgorithm.h"
#include <limits>
#include <sstream>
#include <vector>
#include <cuda_runtime.h>

extern "C" void runCudaKernel(const double* h_matrix, double* h_result,
    size_t rows, size_t cols);

namespace matrix {

    std::string CUDAAlgorithm::name() const {
        int deviceCount = 0;
        cudaGetDeviceCount(&deviceCount);

        std::ostringstream oss;
        oss << "CUDA (Devices: " << deviceCount << ")";
        return oss.str();
    }

    bool CUDAAlgorithm::isAvailable() {
        int deviceCount = 0;
        cudaGetDeviceCount(&deviceCount);
        return deviceCount > 0;
    }

    std::vector<double> CUDAAlgorithm::execute(const Matrix& matrix) {
        if (matrix.empty()) {
            return {};
        }

        size_t rows = matrix.rows();
        size_t cols = matrix.cols();

        std::vector<double> result(cols, std::numeric_limits<double>::lowest());

        runCudaKernel(matrix.raw_data(), result.data(), rows, cols);

        return result;
    }

}