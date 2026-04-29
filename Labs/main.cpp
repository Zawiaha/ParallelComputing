#include <iostream>
#include <memory>
#include <vector>
#include <omp.h>
#include "Matrix.h"
#include "SequentialAlgorithm.h"
#include "ParallelAlgorithm.h"
#include "MPIAlgorithm.h"
#include "CUDAAlgorithm.h"
#include "ExperimentRunner.h"

using namespace matrix;

Matrix generateRandomMatrix(size_t rows, size_t cols) {
    Matrix matrix(rows, cols);
    matrix.fillRandom(-100.0, 100.0);
    return matrix;
}

int main() {
    std::cout << "=== LAB 3: PARALLEL COMPUTING ===\n";
    std::cout << "Task: Find maximum in each matrix column\n";
    std::cout << "OpenMP threads: " << omp_get_max_threads() << "\n";

    // Проверка CUDA
    if (CUDAAlgorithm::isAvailable()) {
        std::cout << "CUDA: Available\n\n";
    }
    else {
        std::cout << "CUDA: Not available (no NVIDIA GPU)\n\n";
    }

    try {
        ExperimentRunner runner;

        runner.addAlgorithm(std::make_shared<SequentialAlgorithm>());
        runner.addAlgorithm(std::make_shared<ParallelAlgorithm>(2));
        runner.addAlgorithm(std::make_shared<ParallelAlgorithm>(4));
        runner.addAlgorithm(std::make_shared<ParallelAlgorithm>(8));

        if (CUDAAlgorithm::isAvailable()) {
            runner.addAlgorithm(std::make_shared<CUDAAlgorithm>());
        }

        std::vector<std::pair<size_t, size_t>> testSizes;
        std::vector<size_t> dims = { 100, 200, 500, 1000, 2000 };

        for (size_t d : dims) {
            testSizes.push_back({ d, d });
        }

        testSizes.push_back({ 5000, 100 });
        testSizes.push_back({ 100, 5000 });

        auto results = runner.runExperiments(testSizes, generateRandomMatrix, 3);

        runner.printResults(results);
        runner.saveToCSV(results, "lab3_results.csv");
        runner.verifyResults(results);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}