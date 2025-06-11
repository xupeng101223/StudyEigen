#include "pch.h"
#include "EigenBase.h"

namespace TestEigenBaseTest0
{
        struct Matrix : 
                //需要注意这个要加上的，否则就不是CRTP的方式哈
                public Eigen::EigenBase<Matrix>
        {
                //需要const的修饰
                Eigen::Index rows() const { return 0; }
                Eigen::Index cols() const { return 0; }
        };
}

TEST(TestEigenBase, Test0) {
        Eigen::EigenBase<TestEigenBaseTest0::Matrix> Base;
        Base.cols();
        Base.rows();
}