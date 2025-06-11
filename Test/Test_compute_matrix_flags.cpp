#include "pch.h"
#include "compute_matrix_flags.h"

TEST(Test_compute_matrix_flags, Test0) {
        //0001 0110 0001
        std::cout << compute_matrix_flags<float, 1, 1, RowMajor, 1, 1>::ret << std::endl;
}