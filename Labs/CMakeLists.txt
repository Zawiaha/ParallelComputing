cmake_minimum_required(VERSION 3.10)
project(MatrixMaxColumns CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(MPI_INCLUDE_PATH "C:/Program Files (x86)/Microsoft SDKs/MPI/Include")
set(MPI_LIBRARY_PATH "C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64")


include_directories(${MPI_INCLUDE_PATH})
link_directories(${MPI_LIBRARY_PATH})


set(MPI_LIBRARIES msmpi)

set(CUDA_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.2")

set(CUDA_INCLUDE_DIR "${CUDA_PATH}/include")
set(CUDA_LIB_DIR "${CUDA_PATH}/lib/x64")
include_directories(${CUDA_INCLUDE_DIRS})
link_directories(${CUDA_LIB_DIR})

find_package(OpenMP REQUIRED)



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/out/includeFile)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/ExperimentRunner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/Matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/ParallelAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/out/src/SequentialAlgorithm.cpp
 "out/src/MPIAlgorithm.cpp" "out/src/CUDAAlgorithm.cpp")


add_executable(matrix_max_columns ${SOURCES})


target_link_libraries(matrix_max_columns PRIVATE OpenMP::OpenMP_CXX)


if(MSVC)
    target_compile_options(matrix_max_columns PRIVATE /W4 /O2 /openmp)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(matrix_max_columns PRIVATE -Wall -Wextra -O2 -fopenmp)
endif()


message(STATUS "OpenMP found: ${OpenMP_CXX_FOUND}")
message(STATUS "Source files: ${SOURCES}")