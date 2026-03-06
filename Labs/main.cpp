// Labs.cpp: определяет точку входа для приложения.
#include <iostream>
#include <memory>
#include <vector>
#include "Matrix.h"
#include "SequentialAlgorithm.h"
#include "ParallelAlgorithm.h"
#include "ExperimentRunner.h"
#include <omp.h>

using namespace matrix;

Matrix generateRandomMatrix(size_t rows, size_t cols) {
    Matrix matrix(rows, cols);
    matrix.fillRandom(-100.0, 100.0);
    return matrix;
}

Matrix generateTestMatrix(size_t rows, size_t cols) {
    Matrix matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = static_cast<double>(i * cols + j);
        }
    }
    return matrix;
}

int main() {
    std::cout << "=== Matrix Column Maximum Performance Analysis ===\n";
    std::cout << "Available threads: " << omp_get_max_threads() << "\n\n";

    try {
        ExperimentRunner runner;

        runner.addAlgorithm(std::make_shared<SequentialAlgorithm>());
        runner.addAlgorithm(std::make_shared<ParallelAlgorithm>(2));
        runner.addAlgorithm(std::make_shared<ParallelAlgorithm>(4));
        runner.addAlgorithm(std::make_shared<ParallelAlgorithm>(8));
        runner.addAlgorithm(std::make_shared<ParallelAlgorithm>(0));

        std::vector<std::pair<size_t, size_t>> testSizes;
        std::vector<size_t> dimensions = { 100, 200, 500, 1000, 2000, 5000 };

        for (size_t dim : dimensions) {
            testSizes.push_back({ dim, dim });
        }

        testSizes.push_back({ 1000, 100 });
        testSizes.push_back({ 100, 1000 });
        testSizes.push_back({ 5000, 10 });
        testSizes.push_back({ 10, 5000 });

        std::cout << "Running experiments...\n";
        auto results = runner.runExperiments(testSizes, generateRandomMatrix, 3);

        runner.verifyResults(results);
        runner.printResults(results);
        runner.saveToCSV(results, "experiment_results.csv");

        std::cout << "\n\n=== Validation on test matrix ===\n";
        Matrix testMatrix = generateTestMatrix(5, 4);

        SequentialAlgorithm seq;
        ParallelAlgorithm par(4);

        auto seqResult = seq.execute(testMatrix);
        auto parResult = par.execute(testMatrix);

        std::cout << "Sequential result: ";
        for (double val : seqResult) std::cout << val << " ";
        std::cout << "\nParallel result:   ";
        for (double val : parResult) std::cout << val << " ";
        std::cout << "\n";

        if (seqResult == parResult) {
            std::cout << "Results match!\n";
        }
        else {
            std::cout << "Results don't match!\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
