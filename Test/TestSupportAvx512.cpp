#include "pch.h"
#include "SupportAvx512.h"

//I5 12600KF ��֧��AVX512 ��T.T
TEST(TestSupportAvx512, Test0) {
        EXPECT_TRUE(!SupportAvx512());
}