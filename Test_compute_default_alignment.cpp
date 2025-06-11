#include "pch.h"
#include "compute_default_alignment.h"

TEST(Test_compute_default_alignment, Test0) {
        //0
        std::cout << compute_default_alignment<float, 30>::value << std::endl;
        //16
        std::cout << compute_default_alignment<float, 32>::value << std::endl;
}