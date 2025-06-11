#include "pch.h"
#include "SupportAvx512.h"

//I5 12600KF ²»Ö§³ÖAVX512 ¹þT.T
TEST(TestSupportAvx512, Test0) {
        EXPECT_TRUE(!SupportAvx512());
}