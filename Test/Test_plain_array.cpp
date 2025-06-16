#include "pch.h"
#include "plain_array.h"

TEST(Test_plain_array, Test0)
{
        // 16±»´¥·¢
        // plain_array<float, 16, 0> a0;

        struct Test_plain_array_T0
        {
                char buff[31];
        };
        plain_array<Test_plain_array_T0, 16, 0> a1;
}