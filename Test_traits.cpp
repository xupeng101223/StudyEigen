#include "pch.h"
#include "traits.h"
#include "Matrix.h"

TEST(Test_traits, Test_traits_Matrix0) {
        /*
        编译器（GCC/Clang/MSVC等）会维护一个模板实例化表（template instantiation cache/table），
        里面根据**模板名+完整参数集（类型、整型常量等）**做唯一标识。
        一旦某种参数实例化过一次，表中已有，后续引用只会复用已实例化的模板元代码。
        这包括 Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>> 这种复杂结构
        */
        /*
        最终汇编的结果会类似于：
                std::cout << 0x53; // 假如 Flags 是 0x53
                std::cout << "Dense";
                std::cout << "float";
        */
        std::cout << Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>>::Flags << std::endl;
        std::cout << typeid(Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>>::StorageKind).name() << std::endl;
        std::cout << typeid(Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>>::Scalar).name() << std::endl;
}