#include "pch.h"
#include <limits>
#include <iostream>

TEST(Test_float_denorm_style, Test0) 
{
        std::cout << "has_denorm (float): "
                << std::numeric_limits<float>::has_denorm
                << std::endl;
}