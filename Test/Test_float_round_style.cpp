#include "pch.h"
#include <limits>
#include <iostream>

TEST(Test_float_round_style, Test0)
{
        std::cout << "round_style (float): "
                << std::numeric_limits<float>::round_style
                << std::endl;
}