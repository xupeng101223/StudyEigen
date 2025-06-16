#include "pch.h"
#include "compute_default_alignment.h"

TEST(Test_compute_default_alignment, Test0) {
        //0 //指在Eigen设计的这套对齐体系里，不能找到一组不会浪费空间、同时满足编译器和硬件高对齐要求的对齐值
        std::cout << compute_default_alignment<float, 30>::value << std::endl;

        //16 EIGEN_MAX_STATIC_ALIGN_BYTES
        std::cout << compute_default_alignment<float, 32>::value << std::endl;

        //16
        std::cout << compute_default_alignment<float, 16>::value << std::endl;
}