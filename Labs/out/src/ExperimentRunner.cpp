// ExperimentRunner.cpp
#include "ExperimentRunner.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <numeric>
#include <algorithm>

namespace matrix {

    void ExperimentRunner::addAlgorithm(std::shared_ptr<MatrixAlgorithm> algorithm) {
        algorithms.push_back(algorithm);
    }

    std::vector<ExperimentResult> ExperimentRunner::runExperiments(
        const std::vector<std::pair<size_t, size_t>>& sizes,
        std::function<Matrix(size_t, size_t)> generateMatrix,
        int repetitions) {

        std::vector<ExperimentResult> allResults;

        for (const auto& size : sizes) {
            size_t rows = size.first;
            size_t cols = size.second;

            std::cout << "\nTesting matrix " << rows << "x" << cols << "\n";

            Matrix matrix = generateMatrix(rows, cols);

            for (auto& algorithm : algorithms) {
                ExperimentResult result;
                result.algorithmName = algorithm->name();
                result.rows = rows;
                result.cols = cols;
                result.matrixSize = rows * cols;

                std::vector<double> times;
                std::vector<double> lastResult;

                for (int rep = 0; rep < repetitions; ++rep) {
                    auto start = std::chrono::high_resolution_clock::now();
                    lastResult = algorithm->execute(matrix);
                    auto end = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    times.push_back(duration.count() / 1000.0);
                }

                result.executionTime = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
                result.result = lastResult;

                allResults.push_back(result);

                std::cout << "  " << std::setw(30) << std::left << algorithm->name()
                    << ": " << std::fixed << std::setprecision(3)
                    << result.executionTime << " ms\n";
            }
        }

        return allResults;
    }

    void ExperimentRunner::printResults(const std::vector<ExperimentResult>& results) const {
        std::cout << "\n\n=== Results Summary ===\n";
        std::cout << std::string(80, '-') << '\n';

        std::cout << std::left
            << std::setw(30) << "Algorithm"
            << std::setw(15) << "Size"
            << std::setw(20) << "Time (ms)" << '\n';

        std::cout << std::string(80, '-') << '\n';

        for (const auto& result : results) {
            std::cout << std::left
                << std::setw(30) << result.algorithmName
                << std::setw(15) << (std::to_string(result.rows) + "x" + std::to_string(result.cols))
                << std::fixed << std::setprecision(3) << std::setw(20) << result.executionTime << '\n';
        }

        std::cout << std::string(80, '-') << '\n';
    }

    void ExperimentRunner::saveToCSV(const std::vector<ExperimentResult>& results,
        const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << '\n';
            return;
        }

        file << "Algorithm,MatrixSize,Rows,Cols,ExecutionTimeMs\n";

        for (const auto& result : results) {
            file << result.algorithmName << ','
                << result.matrixSize << ','
                << result.rows << ','
                << result.cols << ','
                << std::fixed << std::setprecision(3) << result.executionTime << '\n';
        }

        std::cout << "\nResults saved to: " << filename << '\n';
    }

    bool ExperimentRunner::verifyResults(const std::vector<ExperimentResult>& results) const {
        if (results.empty()) return true;

        std::map<std::pair<size_t, size_t>, std::vector<ExperimentResult>> grouped;
        for (const auto& result : results) {
            grouped[{result.rows, result.cols}].push_back(result);
        }

        bool allCorrect = true;

        for (const auto& [size, groupResults] : grouped) {
            if (groupResults.size() < 2) continue;

            const auto& firstResult = groupResults[0].result;

            for (size_t i = 1; i < groupResults.size(); ++i) {
                if (groupResults[i].result != firstResult) {
                    std::cerr << "Error: Results don't match for matrix "
                        << size.first << "x" << size.second << "\n";
                    allCorrect = false;
                }
            }
        }

        if (allCorrect) {
            std::cout << "\nAll algorithms produce identical results.\n";
        }

        return allCorrect;
    }

}