#include "pch.h"
#include "DenseStorage.h"

TEST(TestDenseStorage, Test0) 
{
        Eigen::DenseStorage<float, 10, 2, 5, 0> storage;
        Eigen::DenseStorage<float, 10, 2, 5, 0> storage2 = storage;
}