#include "pch.h"
#include "default_digits10_impl.h"

TEST(Test_default_digits10_impl, Test0) {
        std::cout << default_digits10_impl<float>::run() << std::endl;
}