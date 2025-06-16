#include "pch.h"
#include "EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT.h"
#include "EIGEN_ALIGN_TO_BOUNDARY.h"

TEST(TEST_EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT, Test0) {
        //EIGEN_ALIGN_TO_BOUNDARY(8) int arr[4];
        //EIGEN_MAKE_UNALIGNED_ARRAY_ASSERT(15, arr);
        ////其实就是看全部低位是否存在1，以便于确认arr是否完全对齐
}