#include "pch.h"
#include "traits.h"
#include "Matrix.h"

TEST(Test_traits, Test_traits_Matrix0) {
        /*
        ��������GCC/Clang/MSVC�ȣ���ά��һ��ģ��ʵ������template instantiation cache/table����
        �������**ģ����+���������������͡����ͳ����ȣ�**��Ψһ��ʶ��
        һ��ĳ�ֲ���ʵ������һ�Σ��������У���������ֻ�Ḵ����ʵ������ģ��Ԫ���롣
        ����� Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>> ���ָ��ӽṹ
        */
        /*
        ���ջ��Ľ���������ڣ�
                std::cout << 0x53; // ���� Flags �� 0x53
                std::cout << "Dense";
                std::cout << "float";
        */
        std::cout << Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>>::Flags << std::endl;
        std::cout << typeid(Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>>::StorageKind).name() << std::endl;
        std::cout << typeid(Eigen::traits<Eigen::Matrix<float, 100, 100, RowMajor, 128, 128>>::Scalar).name() << std::endl;
}