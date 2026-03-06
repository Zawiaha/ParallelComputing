cmake_minimum_required(VERSION 3.10)
project(MatrixMaxColumns CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/out/includeFile)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/ExperimentRunner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/Matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/ParallelAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/SequentialAlgorithm.cpp
)


add_executable(matrix_max_columns ${SOURCES})


target_link_libraries(matrix_max_columns PRIVATE OpenMP::OpenMP_CXX)


if(MSVC)
    target_compile_options(matrix_max_columns PRIVATE /W4 /O2 /openmp)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(matrix_max_columns PRIVATE -Wall -Wextra -O2 -fopenmp)
endif()


message(STATUS "OpenMP found: ${OpenMP_CXX_FOUND}")
message(STATUS "Source files: ${SOURCES}")