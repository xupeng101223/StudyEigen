#include "pch.h"
#include "EigenBase.h"

namespace TestEigenBaseTest0
{
        struct Matrix : 
                //��Ҫע�����Ҫ���ϵģ�����Ͳ���CRTP�ķ�ʽ��
                public Eigen::EigenBase<Matrix>
        {
                //��Ҫconst������
                Eigen::Index rows() const { return 0; }
                Eigen::Index cols() const { return 0; }
        };
}

TEST(TestEigenBase, Test0) {
        Eigen::EigenBase<TestEigenBaseTest0::Matrix> Base;
        Base.cols();
        Base.rows();
}