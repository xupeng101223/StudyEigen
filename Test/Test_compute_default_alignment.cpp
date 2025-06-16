#include "pch.h"
#include "compute_default_alignment.h"

TEST(Test_compute_default_alignment, Test0) {
        //0 //ָ��Eigen��Ƶ����׶�����ϵ������ҵ�һ�鲻���˷ѿռ䡢ͬʱ�����������Ӳ���߶���Ҫ��Ķ���ֵ
        std::cout << compute_default_alignment<float, 30>::value << std::endl;

        //16 EIGEN_MAX_STATIC_ALIGN_BYTES
        std::cout << compute_default_alignment<float, 32>::value << std::endl;

        //16
        std::cout << compute_default_alignment<float, 16>::value << std::endl;
}