
// ExperimentRunner.h
#pragma once

#include "MatrixAlgorithm.h"
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <memory>

namespace matrix {

    struct ExperimentResult {
        std::string algorithmName;
        size_t matrixSize;
        size_t rows;
        size_t cols;
        double executionTime;
        std::vector<double> result;
    };

    class ExperimentRunner {
    private:
        std::vector<std::shared_ptr<MatrixAlgorithm>> algorithms;

    public:
        void addAlgorithm(std::shared_ptr<MatrixAlgorithm> algorithm);

        std::vector<ExperimentResult> runExperiments(
            const std::vector<std::pair<size_t, size_t>>& sizes,
            std::function<Matrix(size_t, size_t)> generateMatrix,
            int repetitions = 5
        );

        void printResults(const std::vector<ExperimentResult>& results) const;
        void saveToCSV(const std::vector<ExperimentResult>& results,
            const std::string& filename) const;
        bool verifyResults(const std::vector<ExperimentResult>& results) const;
    };

}